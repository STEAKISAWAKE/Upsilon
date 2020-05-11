
#ifndef __UPSILON_RENDER_VULKANIMAGEVIEWS_H__
#define __UPSILON_RENDER_VULKANIMAGEVIEWS_H__

#include <vector>

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanImageViews
{

public:
    VulkanImageViews(VulkanRHI* rhi);

public:
    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANIMAGEVIEWS_H__