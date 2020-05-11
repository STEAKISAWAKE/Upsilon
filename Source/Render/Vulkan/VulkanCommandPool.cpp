#include "Vulkan/VulkanCommandPool.h"

#include "Vulkan/VulkanRHI.h"

#include "Vulkan/VulkanPhysicalDevice.h"
#include "Vulkan/VulkanDevice.h"

#include "Log.h"

VulkanCommandPool::VulkanCommandPool(VulkanRHI* rhi)
{
    RHI = rhi;
}

void VulkanCommandPool::Initalize()
{
    QueueFamilyIndices queueFamilyIndices = RHI->PhysicalDevice->GetQueueFamilies();

    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    poolInfo.flags = 0;

    if(vkCreateCommandPool(RHI->Device->device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        ULogError("Vulkan Command Pool", "Could not create a command pool!");
    }
}

void VulkanCommandPool::Cleanup()
{
    vkDestroyCommandPool(RHI->Device->device, commandPool, nullptr);
}
