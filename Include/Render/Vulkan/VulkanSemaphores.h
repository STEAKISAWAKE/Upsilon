
#ifndef __UPSILON_RENDER_VULKANSEMAPHORES_H__
#define __UPSILON_RENDER_VULKANSEMAPHORES_H__

#include <vector>

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanSemaphores
{

public:
    VulkanSemaphores(VulkanRHI* rhi);

public:
    std::vector<VkSemaphore> imageAvailableSemaphore;
    std::vector<VkSemaphore> renderFinishedSemaphore;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;

    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANSEMAPHORES_H__
