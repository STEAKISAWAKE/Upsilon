
#ifndef __UPSILON_RENDER_VULKANIMAGEVIEWS_H__
#define __UPSILON_RENDER_VULKANIMAGEVIEWS_H__

#include <vector>

#include "vulkan/vulkan.h"

class VulkanDevice;
class VulkanSwapChain;

class VulkanImageViews
{

public:
    VulkanImageViews(VulkanDevice* device, VulkanSwapChain* swapChain);

public:
    
    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANIMAGEVIEWS_H__