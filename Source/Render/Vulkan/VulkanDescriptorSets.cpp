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

    for(size_t i = 0; i < SwapChain->swapChainImages.size(); i++)
    {
        VkDescriptorBufferInfo bufferInfo = {};
        bufferInfo.buffer = mesh->uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(CameraUniformBuffer);

        VkWriteDescriptorSet descriptorWrite = {};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = descriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;
        descriptorWrite.pImageInfo = nullptr;
        descriptorWrite.pTexelBufferView = nullptr;

        vkUpdateDescriptorSets(Device->device, 1, &descriptorWrite, 0, nullptr);
    }
}