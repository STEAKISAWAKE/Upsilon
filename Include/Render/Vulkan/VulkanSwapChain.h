
#ifndef __UPSILON_RENDER_VULKANSWAPCHAIN_H__
#define __UPSILON_RENDER_VULKANSWAPCHAIN_H__

#include <vector>

#include "vulkan/vulkan.h"

class RenderWindow;

class VulkanPhysicalDevice;
class VulkanDevice;
class VulkanSurface;

class VulkanSwapChain
{

public:
    VulkanSwapChain(RenderWindow* window, VulkanPhysicalDevice* physicalDevice, VulkanDevice* device, VulkanSurface* surface);

public:

    VkSwapchainKHR swapChain;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
 
    RenderWindow* Window;

    VulkanPhysicalDevice* PhysicalDevice;
    VulkanDevice* Device;
    VulkanSurface* Surface;


public:
    void Initalize();
    void Cleanup();

public:
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(RenderWindow* window, const VkSurfaceCapabilitiesKHR& capabilities);

};



#endif // __UPSILON_RENDER_VULKANSWAPCHAIN_H__
