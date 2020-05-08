#include "Vulkan/VulkanFramebuffers.h"

#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanRenderPass.h"
#include "Vulkan/VulkanDevice.h"

#include "Log.h"

VulkanFramebuffers::VulkanFramebuffers(VulkanDevice* device, VulkanSwapChain* swapChain, VulkanRenderPass* renderPass)
{
    Device = device;
    SwapChain = swapChain;
    RenderPass = renderPass;
}

void VulkanFramebuffers::Initalize()
{
    SwapChain->swapChainFramebuffers.resize(SwapChain->swapChainImageViews.size());

    for(size_t i = 0; i < SwapChain->swapChainImageViews.size(); i++)
    {
        VkImageView attachments[] =
        {
            SwapChain->swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = RenderPass->renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = SwapChain->swapChainExtent.width;
        framebufferInfo.height = SwapChain->swapChainExtent.height;
        framebufferInfo.layers = 1;

        if(vkCreateFramebuffer(Device->device, &framebufferInfo, nullptr, &SwapChain->swapChainFramebuffers[i]) != VK_SUCCESS)
        {
            ULogError("Vulkan Framebuffers", "Could not create a framebuffer!");
        }
    }
}

void VulkanFramebuffers::Cleanup()
{
    for(auto framebuffer : SwapChain->swapChainFramebuffers)
    {
        vkDestroyFramebuffer(Device->device, framebuffer, nullptr);
    }
}
