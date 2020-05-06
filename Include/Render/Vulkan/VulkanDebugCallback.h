#ifndef __UPSILON_RENDER_VULKANDEBUGCALLBACK_H__
#define __UPSILON_RENDER_VULKANDEBUGCALLBACK_H__

#include "vulkan/vulkan.h"

class VulkanInstance;

class VulkanDebugCallback
{

public:
    VulkanDebugCallback(VulkanInstance* instance);

public:
    VkDebugUtilsMessengerEXT debugMessenger;
    VulkanInstance* Instance;

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
