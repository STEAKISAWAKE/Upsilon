
#ifndef __UPSILON_RENDER_VULKANDESCRIPTORPOOL_H__
#define __UPSILON_RENDER_VULKANDESCRIPTORPOOL_H__

#include "vulkan/vulkan.h"

class VulkanDevice;
class VulkanSwapChain;

class VulkanDescriptorPool
{

public:
    VulkanDescriptorPool(VulkanDevice* Device, VulkanSwapChain* swapChain);

public:
    VkDescriptorPool descriptorPool;

    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANDESCRIPTORPOOL_H__
