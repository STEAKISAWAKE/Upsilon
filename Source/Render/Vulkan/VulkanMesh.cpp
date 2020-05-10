#include "VulkanMesh.h"

#include "VulkanRHI.h"

#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanCommandBuffers.h"
#include "Vulkan/VulkanBuffers.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanGraphicsPipeline.h"
#include "Vulkan/VulkanDescriptorLayout.h"
#include "Vulkan/VulkanDescriptorPool.h"
#include "Vulkan/VulkanDescriptorSets.h"

VulkanMesh::VulkanMesh(RenderRHI* rhi)
    : RenderMesh(rhi)
{
    VulkanRHI* renderRHI = static_cast<VulkanRHI*>(RHI);
    descriptorSets = new VulkanDescriptorSets(renderRHI->Device, renderRHI->SwapChain, renderRHI->DescriptorPool, renderRHI->DescriptorLayout);
}

void VulkanMesh::Initalize()
{
    VulkanRHI* renderRHI = static_cast<VulkanRHI*>(RHI);
    renderRHI->Buffers->CreateMeshBuffers(this);
}

void VulkanMesh::Cleanup()
{
    VulkanRHI* renderRHI = static_cast<VulkanRHI*>(RHI);

    vkDestroyBuffer(renderRHI->Device->device, indexBuffer, nullptr);
    vkFreeMemory(renderRHI->Device->device, indexBufferMemory, nullptr);

    vkDestroyBuffer(renderRHI->Device->device, vertexBuffer, nullptr);
    vkFreeMemory(renderRHI->Device->device, vertexBufferMemory, nullptr);
}

void VulkanMesh::Draw(int commandBuffersIndex)
{
    VulkanRHI* renderRHI = static_cast<VulkanRHI*>(RHI);

    //vkCmdBindPipeline(renderRHI->CommandBuffers->commandBuffers[commandBuffersIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};

    vkCmdBindVertexBuffers(renderRHI->CommandBuffers->commandBuffers[commandBuffersIndex], 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(renderRHI->CommandBuffers->commandBuffers[commandBuffersIndex], indexBuffer, 0, VK_INDEX_TYPE_UINT32);

    vkCmdBindDescriptorSets(
        renderRHI->CommandBuffers->commandBuffers[commandBuffersIndex], 
        VK_PIPELINE_BIND_POINT_GRAPHICS, 
        static_cast<VulkanShaderPool*>(renderRHI->ShaderPools[0])->GraphicsPipeline->pipelineLayout, 
        0, 
        1, 
        &descriptorSets->descriptorSets[commandBuffersIndex], 
        0, 
        nullptr);
        
    vkCmdDrawIndexed(renderRHI->CommandBuffers->commandBuffers[commandBuffersIndex], static_cast<uint32_t>(Indices.size()), 1, 0, 0, 0);
}

void VulkanMesh::InitalizeUniformBuffers()
{
    VulkanRHI* renderRHI = static_cast<VulkanRHI*>(RHI);

    renderRHI->Buffers->CreateUniformBuffers(this);
}


void VulkanMesh::InitalizeDescriptorSets()
{
    descriptorSets->CreateDescriptorSets(this);
}


void VulkanMesh::CleanupUniformBuffers()
{
    VulkanRHI* renderRHI = static_cast<VulkanRHI*>(RHI);

    for(size_t i = 0; i < renderRHI->SwapChain->swapChainImages.size(); i++)
    {
        vkDestroyBuffer(renderRHI->Device->device,uniformBuffers[i], nullptr);
        vkFreeMemory(renderRHI->Device->device, uniformBuffersMemory[i], nullptr);
    }
}

void VulkanMesh::CleanupDescriptorSets()
{
    descriptorSets->descriptorSets.clear();
}

void VulkanMesh::UpdateUniformBuffers(int imageIndex)
{
    VulkanRHI* renderRHI = static_cast<VulkanRHI*>(RHI);
    
    CUB.projection[1][1] *= -1; // Flip the y scale because glm was designed for opengl
    
    void* data;
    vkMapMemory(renderRHI->Device->device, uniformBuffersMemory[imageIndex], 0, sizeof(CUB), 0, &data);
        memcpy(data, &CUB, sizeof(CUB));
    vkUnmapMemory(renderRHI->Device->device, uniformBuffersMemory[imageIndex]);

}
