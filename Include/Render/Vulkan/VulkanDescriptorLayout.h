
#ifndef __UPSILON_RENDER_VULKANDESCRIPTORLAYOUT_H__
#define __UPSILON_RENDER_VULKANDESCRIPTORLAYOUT_H__

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanDescriptorLayout
{

public:
    VulkanDescriptorLayout(VulkanRHI* rhi);

public:
    VkDescriptorSetLayout descriptorSetLayout;

    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANDESCRIPTORLAYOUT_H__
