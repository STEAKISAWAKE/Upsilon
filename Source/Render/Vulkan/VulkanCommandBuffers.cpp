#include "Vulkan/VulkanCommandBuffers.h"

#include "VulkanRHI.h"

#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanRenderPass.h"
#include "Vulkan/VulkanGraphicsPipeline.h"
#include "Vulkan/VulkanCommandPool.h"

#include "Log.h"

VulkanCommandBuffers::VulkanCommandBuffers(VulkanDevice* device, VulkanSwapChain* swapChain,  VulkanRenderPass* renderPass, VulkanShaderPool* shaders, VulkanCommandPool* commandPool)
{
    Device = device;
    SwapChain = swapChain;
    RenderPass = renderPass;
    Shaders = shaders;
    CommandPool = commandPool;
}

void VulkanCommandBuffers::Initalize()
{
    commandBuffers.resize(SwapChain->swapChainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = CommandPool->commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

    if(vkAllocateCommandBuffers(Device->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
    {
        ULogError("Vulkan Command Buffers", "Could not allocate command buffers!");
    }

    for(size_t i = 0; i < commandBuffers.size(); i++)
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;

        if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
        {
            ULogError("Vulkan Command Buffers", "Could not begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = RenderPass->renderPass;
        renderPassInfo.framebuffer = SwapChain->swapChainFramebuffers[i];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = SwapChain->swapChainExtent;
        
        VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, Shaders->GraphicsPipeline->graphicsPipeline);

            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
        {
            ULogError("Vulkan Command Buffers", "Could not end recording command buffer!");
        }

    }



}

void VulkanCommandBuffers::Cleanup()
{

}

