
#ifndef __UPSILON_RENDER_VULKANCOMMANDBUFFERS_H__
#define __UPSILON_RENDER_VULKANCOMMANDBUFFERS_H__

#include <vector>

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanShaderPool;

class VulkanCommandBuffers
{

public:
    VulkanCommandBuffers(VulkanRHI* rhi);

public:
    std::vector<VkCommandBuffer> commandBuffers;

    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANCOMMANDBUFFERS_H__
