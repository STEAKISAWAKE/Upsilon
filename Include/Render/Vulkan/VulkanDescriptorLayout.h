
#ifndef __UPSILON_RENDER_VULKANDESCRIPTORLAYOUT_H__
#define __UPSILON_RENDER_VULKANDESCRIPTORLAYOUT_H__

#include "vulkan/vulkan.h"

class VulkanDevice;

class VulkanDescriptorLayout
{

public:
    VulkanDescriptorLayout(VulkanDevice* device);

public:
    VkDescriptorSetLayout descriptorSetLayout;

    VulkanDevice* Device;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANDESCRIPTORLAYOUT_H__
