#include "Vulkan/VulkanDescriptorSets.h"

#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanDescriptorPool.h"
#include "Vulkan/VulkanDescriptorLayout.h"
#include "Vulkan/VulkanMesh.h"

#include "Log.h"

VulkanDescriptorSets::VulkanDescriptorSets(VulkanDevice* device, VulkanSwapChain* swapChain, VulkanDescriptorPool* descriptorPool, VulkanDescriptorLayout* descriptorLayout)
{

    Device = device;
    SwapChain = swapChain;
    DescriptorPool = descriptorPool;
    DescriptorLayout = descriptorLayout;

}

void VulkanDescriptorSets::CreateDescriptorSets(VulkanMesh* mesh)
{
    std::vector<VkDescriptorSetLayout> layouts(SwapChain->swapChainImages.size(), DescriptorLayout->descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = DescriptorPool->descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(SwapChain->swapChainImages.size());
    allocInfo.pSetLayouts = layouts.data();

    descriptorSets.resize(SwapChain->swapChainImages.size());
    if(vkAllocateDescriptorSets(Device->device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
    {
        ULogError("Vulkan Descriptor Sets", "Could not allocate descriptor sets!");
    }

}