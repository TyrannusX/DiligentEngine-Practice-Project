/*
* Force GLFW to expose native window handle
*/
#define GLFW_EXPOSE_NATIVE_WIN32

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
#include <cstring>

RendererManager::RendererManager(Window* window)
{
	GLFWwindow* underlyingWindow = window->GetUnderlyingWindow();
	
	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(underlyingWindow, &windowWidth, &windowHeight);
	HWND nativeOsWindow = glfwGetWin32Window(underlyingWindow);


	view_width_ = (uint16_t)windowWidth;
	view_height_ = (uint16_t)windowHeight;

	createInstance();
	setupDebugMessenger();
	pickPhysicalDevice();
}

RendererManager::~RendererManager()
{
	if (enable_validation_layers)
	{
		DestroyDebugUtilsMessengerEXT(vk_instance_, debug_messenger_, nullptr);
	}
	vkDestroyInstance(vk_instance_, nullptr);
}

void RendererManager::PaintNextFrame(StaticEntity& static_entity, int x_modifier, int y_modifier)
{
}

void RendererManager::createInstance()
{
	if(enable_validation_layers && !checkValidationLayerSupport())
	{ 
		throw std::exception("Failed check of validation layer support");
	}

	VkApplicationInfo vkApplicationInfo = {};
	vkApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	vkApplicationInfo.pApplicationName = "Mystical Mana";
	vkApplicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	vkApplicationInfo.pEngineName = "NONE";
	vkApplicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	vkApplicationInfo.apiVersion = VK_API_VERSION_1_2;

	VkInstanceCreateInfo vkInstanceCreateInfo = {};
	vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vkInstanceCreateInfo.pApplicationInfo = &vkApplicationInfo;

	auto extensions = getRequiredExtensions();
	vkInstanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	vkInstanceCreateInfo.ppEnabledExtensionNames = extensions.data();

	vkInstanceCreateInfo.enabledLayerCount = 0;
	VkDebugUtilsMessengerCreateInfoEXT debug_create_info = {};
	if (enable_validation_layers)
	{
		vkInstanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers_.size());
		vkInstanceCreateInfo.ppEnabledLayerNames = validation_layers_.data();
		populateDebugMessengerCreateInfo(debug_create_info);
		/*vkInstanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;*/
	}

	if (vkCreateInstance(&vkInstanceCreateInfo, nullptr, &vk_instance_) != VK_SUCCESS)
	{
		throw std::exception("Failed to create vulkan instance");
	}
}

bool RendererManager::checkValidationLayerSupport()
{
	uint32_t layer_count;
	vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

	std::vector<VkLayerProperties> available_layers(layer_count);
	vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

	for (const char* layer_name : validation_layers_)
	{
		bool layer_found = false;

		for (const auto& layer_properties : available_layers)
		{
			if (strcmp(layer_name, layer_properties.layerName) == 0)
			{
				layer_found = true;
				break;
			}
		}

		if (!layer_found)
		{
			return false;
		}
	}

	return true;
}

void RendererManager::setupDebugMessenger()
{
	if (!enable_validation_layers)
	{
		return;
	}

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(vk_instance_, &createInfo, nullptr, &debug_messenger_) != VK_SUCCESS)
	{
		throw std::exception("Failed to create vulkan layer debug messenger");
	}
}

void RendererManager::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = nullptr;
}

std::vector<const char*> RendererManager::getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	return extensions;
}

void RendererManager::pickPhysicalDevice()
{
	uint32_t device_count = 0;
	vkEnumeratePhysicalDevices(vk_instance_, &device_count, nullptr);

	if (device_count < 1)
	{
		throw std::exception("Failed to find any physical GPUs to use with Vulkan");
	}

	std::vector<VkPhysicalDevice> devices(device_count);
	vkEnumeratePhysicalDevices(vk_instance_, &device_count, devices.data());

	for (const auto& device : devices)
	{
		if (isDeviceSuitable(device))
		{
			vk_physical_device_ = device;
			break;
		}
	}

	if (vk_physical_device_ == VK_NULL_HANDLE)
	{
		throw std::exception("Failed to find suitable GPU");
	}
}

bool RendererManager::isDeviceSuitable(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties device_properties;
	vkGetPhysicalDeviceProperties(device, &device_properties);
	return device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
}

QueueFamilyIndices RendererManager::findQueueFamilies(VkPhysicalDevice device)
{
	throw std::exception();
}

VkResult RendererManager::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vk_instance_, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void RendererManager::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vk_instance_, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr)
	{
		func(instance, debugMessenger, pAllocator);
	}
}