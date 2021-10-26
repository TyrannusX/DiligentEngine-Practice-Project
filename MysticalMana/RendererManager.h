#pragma once

#define PLATFORM_WIN32 1

#include <memory>
#include <string>
#include "Window.h"
#include "StaticEntity.h"
#include "Vertex.h"
#include <PipelineState.h>
#include <EngineFactoryVk.h>
#include <RefCntAutoPtr.hpp>
#include <RenderDevice.h>
#include <DeviceContext.h>
#include <SwapChain.h>
#include <BasicMath.hpp>
#include <MapHelper.hpp>

class RendererManager
{
	private:
		uint16_t m_view_width_;
		uint16_t m_view_height_;

		/*
		* Virtual handle to GPU basically
		*/
		Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_render_device_;

		/*
		* Handle to graphics context. Basically wraps stuff like
		* Buffers, shaders, etc
		*/
		Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_immediate_context_;

		/*
		* Manages the process of painting an image (back buffer) and flipping it
		* to display to the user on screen (front buffer)
		*/
		Diligent::RefCntAutoPtr<Diligent::ISwapChain> m_swap_chain_;

		/*
		* Handle to the graphics/compute pipeline and configures the different stages and mappings
		* to the GPU
		*/
		Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pipeline_state_;

		/*
		* Define the device type
		*/
		Diligent::RENDER_DEVICE_TYPE m_render_device_type = Diligent::RENDER_DEVICE_TYPE_VULKAN;

		/*
		* Define uniform buffer.
		*
		* Uniform buffers contain uniform data.
		* Uniform data act as global variables in the shader/pipeline world.
		* With each invocation of the pipeline, these DO NOT change.
		*/
		Diligent::RefCntAutoPtr<Diligent::IBuffer> m_uniform_buffer_;

		/*
		* Shader Resource Binder
		* 
		* Binds data from application to shader
		*/
		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> m_shader_resource_binder_;

		/*
		* The world+view+projection matrix
		*/
		Diligent::float4x4 m_world_view_projection_matrix_;

		bool enable_validation_ = true;

	public:
		RendererManager(Window* window);
		~RendererManager();
		void UpdateWorld(Diligent::Vector3<float> cameraVector);
		void PaintNextFrame(StaticEntity& static_entity);
		Diligent::RefCntAutoPtr<Diligent::IBuffer> CreateVertexBuffer(StaticEntity& staticEntity);
		Diligent::RefCntAutoPtr<Diligent::IBuffer> CreateIndexBuffer(StaticEntity& staticEntity);

};

