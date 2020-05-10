#ifndef __UPSILON_RENDER_VULKANDESCRIPTORSETS_H__
#define __UPSILON_RENDER_VULKANDESCRIPTORSETS_H__

#include "vulkan/vulkan.h"

class VulkanDevice;
class VulkanSwapChain;
class VulkanDescriptorLayout;
class VulkanDescriptorPool;
class VulkanMesh;

class VulkanDescriptorSets
{

public:
    VulkanDescriptorSets(VulkanDevice* device, VulkanSwapChain* swapChain, VulkanDescriptorPool* descriptorPool, VulkanDescriptorLayout* descriptorLayout);

public:
    std::vector<VkDescriptorSet> descriptorSets;

    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;
    VulkanDescriptorPool* DescriptorPool;
    VulkanDescriptorLayout* DescriptorLayout;

public:
    void CreateDescriptorSets(VulkanMesh* mesh);

};

#endif // __UPSILON_RENDER_VULKANDESCRIPTORSETS_H__