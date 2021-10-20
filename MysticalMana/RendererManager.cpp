/*
* Force GLFW to expose native window handle
*/

#define GLFW_EXPOSE_NATIVE_WIN32 1

/*
* windows.h defines its own versions of these functions
*/
#define NOMINMAX

#include <iostream>
#include "RendererManager.h"
#include "Vertex.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <fstream>
#include <exception>

RendererManager::RendererManager(Window* window)
{
	//Get underlying window and details
	GLFWwindow* underlyingWindow = window->GetUnderlyingWindow();
	
	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(underlyingWindow, &windowWidth, &windowHeight);
	HWND nativeOsWindow = glfwGetWin32Window(underlyingWindow);

	view_width_ = (uint16_t)windowWidth;
	view_height_ = (uint16_t)windowHeight;

	//Initialize Vulkan Device, Context, and Swap Chain
	Diligent::IEngineFactoryVk* engineFactory = Diligent::GetEngineFactoryVk();
	Diligent::EngineVkCreateInfo createInfo;
	engineFactory->CreateDeviceAndContextsVk(createInfo, &render_device_, &immediate_context_);
	Diligent::SwapChainDesc swapChainDesc;
	Diligent::Win32NativeWindow diligentNativeWindowHandle{ nativeOsWindow };
	engineFactory->CreateSwapChainVk(render_device_, immediate_context_, swapChainDesc, diligentNativeWindowHandle, &swap_chain_);

	//Initialize graphics/compute pipeline
	Diligent::GraphicsPipelineStateCreateInfo pipelineCreateInfo;

	//Metadata for the pipeline
	pipelineCreateInfo.PSODesc.Name = "Mystical Mana PSO";
	pipelineCreateInfo.PSODesc.PipelineType = Diligent::PIPELINE_TYPE_GRAPHICS;

	//Define the output (screen in this case)
	pipelineCreateInfo.GraphicsPipeline.NumRenderTargets = 1;
	pipelineCreateInfo.GraphicsPipeline.RTVFormats[0] = swap_chain_->GetDesc().ColorBufferFormat;
	pipelineCreateInfo.GraphicsPipeline.DSVFormat = swap_chain_->GetDesc().DepthBufferFormat;

	//Define the types of primitives the pipeline will output (triangles in this case)
	pipelineCreateInfo.GraphicsPipeline.PrimitiveTopology = Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	/*
	* Define the ratzerizer stage's culling method.
	* Culling will trim parts of objects that dont
	* appear in the projection matrix.
	*
	* CULL_MODE_NONE -> draw everything.
	* CULL_MODE_BACK -> dont draw what's behind something else.
	*/
	pipelineCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode = Diligent::CULL_MODE_BACK;

	/*
	* Set the depth test flag.
	* If enabled, fragments are discarded if they
	* are drawn behind another fragment.
	*/
	pipelineCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = true;

	//Create a shader source stream factory to read shaders from file
	Diligent::RefCntAutoPtr<Diligent::IShaderSourceInputStreamFactory> streamFactory;
	engineFactory->CreateDefaultShaderSourceStreamFactory(nullptr, &streamFactory);

	//Vertex shader handle
	Diligent::ShaderCreateInfo shaderCreateInfo;
	shaderCreateInfo.SourceLanguage = Diligent::SHADER_SOURCE_LANGUAGE_HLSL;
	shaderCreateInfo.pShaderSourceStreamFactory = streamFactory;
	Diligent::RefCntAutoPtr<Diligent::IShader> vertexShaderHandle;
	shaderCreateInfo.Desc.ShaderType = Diligent::SHADER_TYPE_VERTEX;
	shaderCreateInfo.EntryPoint = "main";
	shaderCreateInfo.Desc.Name = "Mystical Mana Vertex Shader";
	shaderCreateInfo.FilePath = "C:\\code\\c++\\MysticalMana\\x64\\Debug\\vertex.hlsl";
	render_device_->CreateShader(shaderCreateInfo, &vertexShaderHandle);

	//Pixel/Fragment shader handle
	Diligent::RefCntAutoPtr<Diligent::IShader> pixelShaderHandle;
	shaderCreateInfo.Desc.ShaderType = Diligent::SHADER_TYPE_PIXEL;
	shaderCreateInfo.EntryPoint = "main";
	shaderCreateInfo.Desc.Name = "Mystical Mana Pixel Shader";
	shaderCreateInfo.FilePath = "C:\\code\\c++\\MysticalMana\\x64\\Debug\\fragment.hlsl";
	render_device_->CreateShader(shaderCreateInfo, &pixelShaderHandle);

	//Define uniform buffer.
	Diligent::BufferDesc bufferDesc;
	bufferDesc.Name = "Mystical Mana Vertex Shader Constants";
	bufferDesc.Size = sizeof(Diligent::float4x4);
	bufferDesc.Usage = Diligent::USAGE_DYNAMIC;
	bufferDesc.BindFlags = Diligent::BIND_UNIFORM_BUFFER;
	bufferDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;
	render_device_->CreateBuffer(bufferDesc, nullptr, &uniform_buffer_);

	/*
	* Define the layout of the data being passed through
	* the vertex buffer. Basically, define metadata.
	*/
	Diligent::LayoutElement layoutElements[] =
	{
		//Attribute 0 is the vertex position
		Diligent::LayoutElement
		{
			0, //Attribute number that the shader will pull from its struct
			0, //Buffer slot (defaults to 0)
			3, //Number of components (position is x,y,z
			Diligent::VT_FLOAT32, //component value type
			Diligent::False //Normalized?
		},

		//Attribute 1 is the vertex color
		Diligent::LayoutElement
		{
			1,
			0,
			4,
			Diligent::VT_FLOAT32,
			Diligent::False
		}
	};
	pipelineCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = layoutElements;
	pipelineCreateInfo.GraphicsPipeline.InputLayout.NumElements = _countof(layoutElements);

	//Bind shaders to pipeline
	pipelineCreateInfo.pVS = vertexShaderHandle;
	pipelineCreateInfo.pPS = pixelShaderHandle;

	//Define the default shader variable type
	pipelineCreateInfo.PSODesc.ResourceLayout.DefaultVariableType = Diligent::SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

	//Finally, pass in the pipeline create struct to create the pipeline
	render_device_->CreateGraphicsPipelineState(pipelineCreateInfo, &pipeline_state_);

	//Bind uniform buffer in thia application to the shader's constant variable (look at vertex shader)
	pipeline_state_->GetStaticVariableByName(Diligent::SHADER_TYPE_VERTEX, "Constants")->Set(uniform_buffer_);

	//Create the resource binder and bind all static resources to this (in this case the uniform buffer data)
	pipeline_state_->CreateShaderResourceBinding(&shader_resource_binder_, true);
}

RendererManager::~RendererManager()
{

}

void RendererManager::PaintNextFrame(StaticEntity& static_entity, int x_modifier, int y_modifier)
{
	//
	//Define the color to use for the render target background
	const float clearColor[] = { 0.350f,  0.350f,  0.350f, 1.0f };

	//Get handle to the render target (laptop screen) back buffer (drawing not yet shown to user) from the swap chain
	Diligent::ITextureView* renderTargetHandle = swap_chain_->GetCurrentBackBufferRTV();

	//Get handle to the depth buffer
	Diligent::ITextureView* depthTargetHandle = swap_chain_->GetDepthBufferDSV();

	//Set the swap chain's render target (screen)
	immediate_context_->SetRenderTargets(1, &renderTargetHandle, depthTargetHandle, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	//Clear buffers (think erasing a whiteboard to start next drawing)
	immediate_context_->ClearRenderTarget(renderTargetHandle, clearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	immediate_context_->ClearDepthStencil(depthTargetHandle, Diligent::CLEAR_DEPTH_FLAG, 1.0f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	/*
	* Map the uniform data.
	* 
	* Use the immediate context to manage the process.
	* Provide the uniform buffer which holds the application data.
	* Peform a write operation to the shader/pipeline
	* Invalidate the previous value
	*/
	Diligent::MapHelper<Diligent::float4x4> CBConstants(immediate_context_, uniform_buffer_, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD);
	*CBConstants = world_view_projection_matrix_.Transpose();

	/*
	* Bind the vertex buffer of the static entity to the pipeline.
	* 
	* Diligent allows you to set a collection of vertex buffers.
	* Here we are setting one currently. We start at the beginning.
	* We use the specified transition mode to let Diligent transition 
	* buffers to their proper state automatically.
	* The final flag tells Diligent to reset/drop previous vertex buffers.
	*/
	Diligent::Uint64 offset = 0;
	Diligent::IBuffer* buffers[] = { static_entity.vertex_buffer };
	immediate_context_->SetVertexBuffers(0, 1, buffers, &offset, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION, Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);

	/*
	* Bind index buffer
	*/
	immediate_context_->SetIndexBuffer(static_entity.index_buffer, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	//Set the immediate rendering context's graphics pipeline to use
	immediate_context_->SetPipelineState(pipeline_state_);

	/*
	* Commit shader resources using the resource binder.
	* 
	* This takes all shader related setup stuff housed internally in Diligent
	* and flushes it down to the graphics pipeline.
	* Think in terms of a DB commit in SQL.
	* Operations dont take affect until you commit
	*/
	immediate_context_->CommitShaderResources(shader_resource_binder_, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	/*
	* Define the draw attributes
	* 
	* We want to draw using indexes and a specified number of them.
	* We also want the engine to verify the state of the vertex and index buffers.
	*/
	Diligent::DrawIndexedAttribs indexedAttributes;
	indexedAttributes.IndexType = Diligent::VT_UINT32;
	indexedAttributes.NumIndices = 36;
	indexedAttributes.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;

	//Use the immediate context to render the next frame (draws on the back buffer)
	immediate_context_->DrawIndexed(indexedAttributes);

	//Use the swap chain to flip the back buffer to the front buffer (front gets moved to back)
	swap_chain_->Present();
}

Diligent::RefCntAutoPtr<Diligent::IBuffer> RendererManager::CreateVertexBuffer(StaticEntity & staticEntity)
{
	Diligent::BufferDesc bufferDesc;
	bufferDesc.Name = "Mystical Mana Vertex Buffer";
	bufferDesc.Usage = Diligent::USAGE_IMMUTABLE;
	bufferDesc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
	bufferDesc.Size = sizeof(staticEntity.vertices);

	Diligent::BufferData bufferData;
	bufferData.pData = staticEntity.vertices;
	bufferData.DataSize = sizeof(staticEntity.vertices);

	Diligent::RefCntAutoPtr<Diligent::IBuffer> buffer;
	render_device_->CreateBuffer(bufferDesc, &bufferData, &buffer);
	return buffer;
}

Diligent::RefCntAutoPtr<Diligent::IBuffer> RendererManager::CreateIndexBuffer(StaticEntity& staticEntity)
{
	Diligent::BufferDesc bufferDesc;
	bufferDesc.Name = "Mystical Mana Index Buffer";
	bufferDesc.Usage = Diligent::USAGE_IMMUTABLE;
	bufferDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
	bufferDesc.Size = sizeof(staticEntity.indices);

	Diligent::BufferData bufferData;
	bufferData.pData = staticEntity.indices;
	bufferData.DataSize = sizeof(staticEntity.indices);

	Diligent::RefCntAutoPtr<Diligent::IBuffer> buffer;
	render_device_->CreateBuffer(bufferDesc, &bufferData, &buffer);
	return buffer;
}