
#ifndef __UPSILON_RENDER_VULKANCOMMANDPOOL_H__
#define __UPSILON_RENDER_VULKANCOMMANDPOOL_H__

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanCommandPool
{

public:
    VulkanCommandPool(VulkanRHI* rhi);

public:
    VkCommandPool commandPool;

    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANCOMMANDPOOL_H__
