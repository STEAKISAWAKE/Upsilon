
#ifndef __UPSILON_RENDER_VULKANSWAPCHAIN_H__
#define __UPSILON_RENDER_VULKANSWAPCHAIN_H__

#include <vector>

#include "vulkan/vulkan.h"

class RenderWindow;
class VulkanRHI;

class VulkanSwapChain
{

public:
    VulkanSwapChain(VulkanRHI* rhi);

public:

    VkSwapchainKHR swapChain;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

public:
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(RenderWindow* window, const VkSurfaceCapabilitiesKHR& capabilities);

};



#endif // __UPSILON_RENDER_VULKANSWAPCHAIN_H__
