#include "Vulkan/VulkanDescriptorPool.h"

#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanSwapChain.h"

#include "Log.h"

VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice* device, VulkanSwapChain* swapChain)
{
    Device = device;
    SwapChain = swapChain;
}

void VulkanDescriptorPool::Initalize()
{
    VkDescriptorPoolSize poolSize = {};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = static_cast<uint32_t>(SwapChain->swapChainImages.size());

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = static_cast<uint32_t>(SwapChain->swapChainImages.size());

    if(vkCreateDescriptorPool(Device->device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
    {
        ULogError("Vulkan Descriptor Pool", "Could not create descriptor pool!");
    }
}

void VulkanDescriptorPool::Cleanup()
{
    vkDestroyDescriptorPool(Device->device, descriptorPool, nullptr);
}
