#include "VulkanDescriptorLayout.h"

#include "Vulkan/VulkanRHI.h"

#include "Vulkan/VulkanDevice.h"

#include "Log.h"

VulkanDescriptorLayout::VulkanDescriptorLayout(VulkanRHI* rhi)
{
    RHI = rhi;
}

void VulkanDescriptorLayout::Initalize()
{
    VkDescriptorSetLayoutBinding cubLayoutBinding = {};
    cubLayoutBinding.binding = 0;
    cubLayoutBinding.descriptorCount = 1;
    cubLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    cubLayoutBinding.pImmutableSamplers = nullptr;
    cubLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;


    VkDescriptorSetLayoutCreateInfo layoutInfo = {};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &cubLayoutBinding;

    if(vkCreateDescriptorSetLayout(RHI->Device->device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
    {
        ULogError("Vulkan Descriptor Set Layout", "Could not create descriptor set layout!");
    }
}

void VulkanDescriptorLayout::Cleanup()
{
    vkDestroyDescriptorSetLayout(RHI->Device->device, descriptorSetLayout, nullptr);
}
