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


class RendererManager
{
	private:
		uint16_t view_width_;
		uint16_t view_height_;

		/*
		* Virtual handle to GPU basically
		*/
		Diligent::RefCntAutoPtr<Diligent::IRenderDevice> render_device_;

		/*
		* Handle to graphics context. Basically wraps stuff like
		* Buffers, shaders, etc
		*/
		Diligent::RefCntAutoPtr<Diligent::IDeviceContext> immediate_context_;

		/*
		* Manages the process of painting an image (back buffer) and flipping it
		* to display to the user on screen (front buffer)
		*/
		Diligent::RefCntAutoPtr<Diligent::ISwapChain> swap_chain_;

		/*
		* Handle to the graphics/compute pipeline and configures the different stages and mappings
		* to the GPU
		*/
		Diligent::RefCntAutoPtr<Diligent::IPipelineState> pipeline_state_;

		/*
		* Define the device type
		*/
		Diligent::RENDER_DEVICE_TYPE render_device_type = Diligent::RENDER_DEVICE_TYPE_VULKAN;

		bool enable_validation_ = true;

	public:
		RendererManager(Window* window);
		~RendererManager();
		void PaintNextFrame(StaticEntity& static_entity, int x_modifier, int y_modifier);
};

