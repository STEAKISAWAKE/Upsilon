#include "VulkanDevice.h"

#include <set>

#include "Vulkan/VulkanRHI.h"

#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanPhysicalDevice.h"

#include "Log.h"

VulkanDevice::VulkanDevice(VulkanRHI* rhi)
{
    RHI = rhi;
}

void VulkanDevice::Initalize()
{
    QueueFamilyIndices indices = RHI->PhysicalDevice->GetQueueFamilies();

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for(uint32_t queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures = {};
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    
    createInfo.enabledExtensionCount = static_cast<uint32_t>(VulkanPhysicalDevice::deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = VulkanPhysicalDevice::deviceExtensions.data();

    if(VulkanInstance::enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanInstance::validationLayers.size());
        createInfo.ppEnabledLayerNames = VulkanInstance::validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if(vkCreateDevice(RHI->PhysicalDevice->physicalDevice, &createInfo, nullptr, &device))
    {
        ULogError("Vulkan Device", "Could not create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}

void VulkanDevice::Cleanup()
{
    vkDestroyDevice(device, nullptr);
}
