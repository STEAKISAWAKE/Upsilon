
#ifndef __UPSILON_RENDER_VULKANGRAPHICSPIPELINE_H__
#define __UPSILON_RENDER_VULKANGRAPHICSPIPELINE_H__

#include "vulkan/vulkan.h"

class ShaderPool;

class VulkanDevice;
class VulkanSwapChain;
class VulkanRenderPass;

class VulkanGraphicsPipeline
{

public:
    VulkanGraphicsPipeline(VulkanDevice* device, VulkanSwapChain* swapChain, VulkanRenderPass* renderPass, ShaderPool* shaders);

public:
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    ShaderPool* Shaders;
    
    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;
    VulkanRenderPass* RenderPass;

public:
    void Initalize();
    void Cleanup();

};  

#endif // __UPSILON_RENDER_VULKANGRAPHICSPIPELINE_H__
