#include "Vulkan/VulkanFramebuffers.h"

#include "Vulkan/VulkanRHI.h"

#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanRenderPass.h"
#include "Vulkan/VulkanDevice.h"

#include "Log.h"

VulkanFramebuffers::VulkanFramebuffers(VulkanRHI* rhi)
{
    RHI = rhi;
}

void VulkanFramebuffers::Initalize()
{
    RHI->SwapChain->swapChainFramebuffers.resize(RHI->SwapChain->swapChainImageViews.size());

    for(size_t i = 0; i < RHI->SwapChain->swapChainImageViews.size(); i++)
    {
        VkImageView attachments[] =
        {
            RHI->SwapChain->swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = RHI->RenderPass->renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = RHI->SwapChain->swapChainExtent.width;
        framebufferInfo.height = RHI->SwapChain->swapChainExtent.height;
        framebufferInfo.layers = 1;

        if(vkCreateFramebuffer(RHI->Device->device, &framebufferInfo, nullptr, &RHI->SwapChain->swapChainFramebuffers[i]) != VK_SUCCESS)
        {
            ULogError("Vulkan Framebuffers", "Could not create a framebuffer!");
        }
    }
}

void VulkanFramebuffers::Cleanup()
{
    for(auto framebuffer : RHI->SwapChain->swapChainFramebuffers)
    {
        vkDestroyFramebuffer(RHI->Device->device, framebuffer, nullptr);
    }
}
