#ifndef __UPSILON_RENDER_VULKANRHI_H__
#define __UPSILON_RENDER_VULKANRHI_H__

#include "RenderRHI.h"

class VulkanInstance;
class VulkanDebugCallback;
class VulkanPhysicalDevice;
class VulkanDevice;

class VulkanRHI
    : public RenderRHI
{

    RTTR_ENABLE(RenderRHI)

public:
    VulkanRHI();
    ~VulkanRHI();

    VulkanInstance* Instance;
    VulkanDebugCallback* DebugCallback;
    VulkanPhysicalDevice* PhysicalDevice;
    VulkanDevice* Device;

public:
    void Initalize() override;
    void Cleanup() override;

public:

};

#endif // __UPSILON_RENDER_RENDERRHI_H__
