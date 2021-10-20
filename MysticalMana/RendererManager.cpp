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
	* In this case we dont want to cull.
	*/
	pipelineCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode = Diligent::CULL_MODE_NONE;

	/*
	* Set the depth test flag.
	* If enabled, fragments are discarded if they
	* are drawn behind another fragment.
	* In this case, we dont want to depth test
	*/
	pipelineCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = false;

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

	pipelineCreateInfo.pVS = vertexShaderHandle;
	pipelineCreateInfo.pPS = pixelShaderHandle;

	//Finally, pass in the pipeline create struct to create the pipeline
	render_device_->CreateGraphicsPipelineState(pipelineCreateInfo, &pipeline_state_);
}

RendererManager::~RendererManager()
{

}

void RendererManager::PaintNextFrame(StaticEntity& static_entity, int x_modifier, int y_modifier)
{
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

	//Set the immediate rendering context's graphics pipeline to use
	immediate_context_->SetPipelineState(pipeline_state_);

	/*
	* Shaders receive the data from the application
	* but shaders are dumb and dont know what the data is about.
	* You have to define the layout/attributes so the shaders know whats what.
	* 
	* In this case, we just want the pipeline to process 3 vertices
	*/
	Diligent::DrawAttribs drawAttributes;
	drawAttributes.NumVertices = 3;

	//Use the immediate context to render the next frame (draws on the back buffer)
	immediate_context_->Draw(drawAttributes);

	//Use the swap chain to flip the back buffer to the front buffer (front gets moved to back)
	swap_chain_->Present();
}