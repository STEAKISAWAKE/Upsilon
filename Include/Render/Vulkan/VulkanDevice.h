
#ifndef __UPSILON_RENDER_VULKANDEVICE_H__
#define __UPSILON_RENDER_VULKANDEVICE_H__

#include "vulkan/vulkan.h"

class VulkanPhysicalDevice;

class VulkanDevice
{

public:
    VulkanDevice(VulkanPhysicalDevice* physicalDevice);

public:
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    static const int MAX_FRAMES_IN_FLIGHT = 2;

    VulkanPhysicalDevice* PhysicalDevice;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANDEVICE_H__

