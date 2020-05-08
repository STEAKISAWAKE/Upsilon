
#ifndef __UPSILON_RENDER_VULKANSEMAPHORES_H__
#define __UPSILON_RENDER_VULKANSEMAPHORES_H__

#include <vector>

#include "vulkan/vulkan.h"

class VulkanDevice;
class VulkanSwapChain;

class VulkanSemaphores
{

public:
    VulkanSemaphores(VulkanDevice* device, VulkanSwapChain* swapChain);

public:
    std::vector<VkSemaphore> imageAvailableSemaphore;
    std::vector<VkSemaphore> renderFinishedSemaphore;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;

    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANSEMAPHORES_H__
