#include "Vulkan/VulkanCommandPool.h"
#include "Vulkan/VulkanPhysicalDevice.h"
#include "Vulkan/VulkanDevice.h"

#include "Log.h"

VulkanCommandPool::VulkanCommandPool(VulkanDevice* device, VulkanPhysicalDevice* physicalDevice)
{
    PhysicalDevice = physicalDevice;
    Device = device;
}

void VulkanCommandPool::Initalize()
{
    QueueFamilyIndices queueFamilyIndices = PhysicalDevice->GetQueueFamilies();

    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    poolInfo.flags = 0;

    if(vkCreateCommandPool(Device->device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        ULogError("Vulkan Command Pool", "Could not create a command pool!");
    }
}

void VulkanCommandPool::Cleanup()
{
    vkDestroyCommandPool(Device->device, commandPool, nullptr);
}
