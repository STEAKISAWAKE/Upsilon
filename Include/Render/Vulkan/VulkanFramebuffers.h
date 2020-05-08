
#ifndef __UPSILON_RENDER_VULKANFRAMEBUFFERS_H__
#define __UPSILON_RENDER_VULKANFRAMEBUFFERS_H__

class VulkanDevice;
class VulkanSwapChain;
class VulkanRenderPass;

class VulkanFramebuffers
{

public:
    VulkanFramebuffers(VulkanDevice* device, VulkanSwapChain* swapChain, VulkanRenderPass* renderPass);

public:
    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;
    VulkanRenderPass* RenderPass;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANFRAMEBUFFERS_H__