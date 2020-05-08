
#ifndef __UPSILON_RENDER_VULKANRENDERPASS_H__
#define __UPSILON_RENDER_VULKANRENDERPASS_H__

#include "vulkan/vulkan.h"

class VulkanDevice;
class VulkanSwapChain;

class VulkanRenderPass
{

public:
    VulkanRenderPass(VulkanDevice* device, VulkanSwapChain* swapChain);

public:
    VkRenderPass renderPass;

    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;

public:
    void Initalize();
    void Cleanup();

};

#endif //  __UPSILON_RENDER_VULKANRENDERPASS_H__