#include "VulkanDevice.h"

#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanPhysicalDevice.h"

#include "Log.h"

VulkanDevice::VulkanDevice(VulkanPhysicalDevice* physicalDevice)
{
    PhysicalDevice = physicalDevice;
}

void VulkanDevice::Initalize()
{
    QueueFamilyIndices indices = PhysicalDevice->GetQueueFamilies();

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures = {};
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if(VulkanInstance::enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanInstance::validationLayers.size());
        createInfo.ppEnabledLayerNames = VulkanInstance::validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if(vkCreateDevice(PhysicalDevice->physicalDevice, &createInfo, nullptr, &device))
    {
        ULogError("Vulkan Device", "Could not create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

void VulkanDevice::Cleanup()
{
    vkDestroyDevice(device, nullptr);
}
