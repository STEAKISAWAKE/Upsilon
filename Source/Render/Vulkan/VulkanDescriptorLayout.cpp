#include "VulkanDescriptorLayout.h"

#include "Vulkan\VulkanDevice.h"

#include "Log.h"

VulkanDescriptorLayout::VulkanDescriptorLayout(VulkanDevice* device)
{
    Device = device;
}

void VulkanDescriptorLayout::Initalize()
{
    VkDescriptorSetLayoutBinding cubLayoutBinding = {};
    cubLayoutBinding.binding = 0;
    cubLayoutBinding.descriptorCount = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    cubLayoutBinding.descriptorCount = 1;
    cubLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    cubLayoutBinding.pImmutableSamplers = nullptr;


    VkDescriptorSetLayoutCreateInfo layoutInfo = {};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &cubLayoutBinding;

    if(vkCreateDescriptorSetLayout(Device->device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
    {
        ULogError("Vulkan Descriptor Set Layout", "Could not create descriptor set layout!");
    }
}

void VulkanDescriptorLayout::Cleanup()
{
    vkDestroyDescriptorSetLayout(Device->device, descriptorSetLayout, nullptr);
}
