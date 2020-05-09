#ifndef __UPSILON_RENDER_VULKANRHI_H__
#define __UPSILON_RENDER_VULKANRHI_H__

#include "RenderRHI.h"

class Render;

class VulkanInstance;
class VulkanDebugCallback;
class VulkanSurface;
class VulkanPhysicalDevice;
class VulkanDevice;
class VulkanSwapChain;
class VulkanImageViews;
class VulkanGraphicsPipeline;
class VulkanRenderPass;
class VulkanFramebuffers;
class VulkanCommandPool;
class VulkanCommandBuffers;
class VulkanSemaphores;
class VulkanBuffers;

class VulkanRHI
    : public RenderRHI
{

    RTTR_ENABLE(RenderRHI)

public:
    VulkanRHI();
    VulkanRHI(Render* renderer);
    ~VulkanRHI();

public:
    VulkanInstance* Instance;
    VulkanDebugCallback* DebugCallback;
    VulkanSurface* Surface;
    VulkanPhysicalDevice* PhysicalDevice;
    VulkanDevice* Device;
    VulkanSwapChain* SwapChain;
    VulkanImageViews* ImageViews;
    VulkanGraphicsPipeline* GraphicsPipeline;
    VulkanRenderPass* RenderPass;
    VulkanFramebuffers* Framebuffers;
    VulkanCommandPool* CommandPool;
    VulkanCommandBuffers* CommandBuffers;
    VulkanSemaphores* Semaphores;
    VulkanBuffers* Buffers;

public:
    void Initalize() override;
    void Cleanup() override;

    void InitalizeMeshes() override;
    void CleanupMeshes() override;

    void InitalizeShaders() override;
    void CleanupShaders(bool everything) override;

    void RecreateSwapChain() override;
    void CleanupSwapChain();

    void DrawFrame() override;

    void FramebufferResized() override;

    ShaderPool* CreateShaderPool() override;
    Shader* CreateShader(int shaderIndex, ShaderType type, const std::vector<char>& code) override;
    RenderMesh* CreateMesh();

private:
    bool framebufferResized = false;

};

/* A handle for the graphics pipeline shaders */
class VulkanShaderPool 
    : public ShaderPool
{

public:
    VulkanShaderPool(VulkanDevice* device, VulkanSwapChain* swapChain, VulkanRenderPass* renderPass);

public:
    VulkanGraphicsPipeline* GraphicsPipeline; // Every group of vulkan shaders needs a new pipeline

    VulkanDevice* Device; 
    VulkanSwapChain* SwapChain;
    VulkanRenderPass* RenderPass;

    void Initalize() override;
    void Cleanup(bool everything) override;

};



#endif // __UPSILON_RENDER_RENDERRHI_H__
