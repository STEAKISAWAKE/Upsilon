
#ifndef __UPSILON_RENDER_VULKANCOMMANDPOOL_H__
#define __UPSILON_RENDER_VULKANCOMMANDPOOL_H__

#include "vulkan/vulkan.h"

class VulkanPhysicalDevice;
class VulkanDevice;

class VulkanCommandPool
{

public:
    VulkanCommandPool(VulkanDevice* device, VulkanPhysicalDevice* physicalDevice);

public:
    VkCommandPool commandPool;

    VulkanPhysicalDevice* PhysicalDevice;
    VulkanDevice* Device;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANCOMMANDPOOL_H__
