
#ifndef __UPSILON_RENDER_VULKANCOMMANDBUFFERS_H__
#define __UPSILON_RENDER_VULKANCOMMANDBUFFERS_H__

#include <vector>

#include "vulkan/vulkan.h"

class VulkanShaderPool;

class VulkanDevice;
class VulkanSwapChain;
class VulkanRenderPass;
class VulkanCommandPool;

class VulkanCommandBuffers
{

public:
    VulkanCommandBuffers(VulkanDevice* device, VulkanSwapChain* swapChain, VulkanRenderPass* renderPass, VulkanShaderPool* shaders, VulkanCommandPool* commandPool);

public:
    std::vector<VkCommandBuffer> commandBuffers;

    VulkanShaderPool* Shaders;

    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;
    VulkanRenderPass* RenderPass;
    VulkanCommandPool* CommandPool;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANCOMMANDBUFFERS_H__
