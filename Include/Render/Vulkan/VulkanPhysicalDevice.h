
#ifndef __UPSILON_RENDER_VULKANPHYSICALDEVICE_H__
#define __UPSILON_RENDER_VULKANPHYSICALDEVICE_H__

#include <optional>

#include "vulkan/vulkan.h"

class VulkanInstance;
struct QueueFamilyIndices;

class VulkanPhysicalDevice
{

public:
    VulkanPhysicalDevice(VulkanInstance* instance);

public:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VulkanInstance* Instance;

public:
    void PickPhysicalDevice();
    QueueFamilyIndices GetQueueFamilies();

public:
    static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    static bool IsDeviceSuitable(VkPhysicalDevice device);

};

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;

    bool isComplete();
};

#endif // __UPSILON_RENDER_VULKANPHYSICALDEVICE_H__
