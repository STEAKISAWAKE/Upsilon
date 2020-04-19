#include "VulkanRenderRHI.h"

#include <GLFW/glfw3.h>

#include "Log.h"

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<VulkanRenderRHI>("VulkanRenderRHI")
        .constructor<>()
        
        .method("Initalize", &VulkanRenderRHI::Initalize)
        .method("Cleanup", &VulkanRenderRHI::Cleanup)
    ;

}

void VulkanRenderRHI::Initalize()
{
    CreateInstance();
}


void VulkanRenderRHI::Cleanup()
{
    vkDestroyInstance(instance, nullptr);
}


void VulkanRenderRHI::CreateInstance()
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Upsilon Application";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "Upsilon";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        Log("Vulkan Instance", "Failed to create instance!");
    }
}