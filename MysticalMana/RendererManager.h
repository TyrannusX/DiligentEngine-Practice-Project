#pragma once
#include <memory>
#include <string>
#include "Window.h"
#include "StaticEntity.h"
#include "Vertex.h"
#include "QueueFamilyIndices.h"

class RendererManager
{
	private:
		uint16_t view_width_;
		uint16_t view_height_;
		VkInstance vk_instance_;
		VkPhysicalDevice vk_physical_device_;
		VkDebugUtilsMessengerEXT debug_messenger_;
		const std::vector<const char*> validation_layers_ =
		{
			"VK_LAYER_KHRONOS_validation"
		};
		const bool enable_validation_layers = true;

		void createInstance();
		bool checkValidationLayerSupport();
		void setupDebugMessenger();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		std::vector<const char*> getRequiredExtensions();
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	public:
		RendererManager(Window* window);
		~RendererManager();
		void PaintNextFrame(StaticEntity& static_entity, int x_modifier, int y_modifier);
};

