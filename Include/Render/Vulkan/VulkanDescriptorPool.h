
#ifndef __UPSILON_RENDER_VULKANDESCRIPTORPOOL_H__
#define __UPSILON_RENDER_VULKANDESCRIPTORPOOL_H__

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanDescriptorPool
{

public:
    VulkanDescriptorPool(VulkanRHI* rhi);

public:
    VkDescriptorPool descriptorPool;

    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANDESCRIPTORPOOL_H__
