
#ifndef __UPSILON_RENDER_VULKANRENDERPASS_H__
#define __UPSILON_RENDER_VULKANRENDERPASS_H__

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanRenderPass
{

public:
    VulkanRenderPass(VulkanRHI* rhi);

public:
    VkRenderPass renderPass;

    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

};

#endif //  __UPSILON_RENDER_VULKANRENDERPASS_H__