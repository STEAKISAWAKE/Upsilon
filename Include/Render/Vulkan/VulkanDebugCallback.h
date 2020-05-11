#ifndef __UPSILON_RENDER_VULKANDEBUGCALLBACK_H__
#define __UPSILON_RENDER_VULKANDEBUGCALLBACK_H__

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanDebugCallback
{

public:
    VulkanDebugCallback(VulkanRHI* rhi);

public:
    VkDebugUtilsMessengerEXT debugMessenger;
    
    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

public:
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

    static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

};

#endif // __UPSILON_RENDER_VULKANDEBUGCALLBACK_H__
