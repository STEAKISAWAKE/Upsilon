
#ifndef __UPSILON_RENDER_VULKANPHYSICALDEVICE_H__
#define __UPSILON_RENDER_VULKANPHYSICALDEVICE_H__

#include <optional>
#include <vector>

#include "vulkan/vulkan.h"

class VulkanInstance;
class VulkanSurface;

struct QueueFamilyIndices;
struct SwapChainSupportDetails;

class VulkanPhysicalDevice
{

public:
    VulkanPhysicalDevice(VulkanInstance* instance, VulkanSurface* surface);

public:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    VulkanInstance* Instance;
    VulkanSurface*  Surface;

    static const std::vector<const char*> deviceExtensions;

public:
    void PickPhysicalDevice();
    QueueFamilyIndices GetQueueFamilies();

public:
    static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VulkanSurface* surface);
    static bool IsDeviceSuitable(VkPhysicalDevice device, VulkanSurface* surface);
    static bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VulkanSurface* surface);

};

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete();
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

#endif // __UPSILON_RENDER_VULKANPHYSICALDEVICE_H__
