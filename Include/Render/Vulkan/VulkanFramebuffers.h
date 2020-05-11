
#ifndef __UPSILON_RENDER_VULKANFRAMEBUFFERS_H__
#define __UPSILON_RENDER_VULKANFRAMEBUFFERS_H__

class VulkanRHI;

class VulkanFramebuffers
{

public:
    VulkanFramebuffers(VulkanRHI* rhi);

public:
    VulkanRHI* RHI;

public:
    void Initalize();
    void Cleanup();

};

#endif // __UPSILON_RENDER_VULKANFRAMEBUFFERS_H__