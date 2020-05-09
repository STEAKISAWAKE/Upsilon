#include "VulkanMesh.h"

#include "VulkanRHI.h"

#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanCommandBuffers.h"
#include "Vulkan/VulkanBuffers.h"

VulkanMesh::VulkanMesh(RenderRHI* rhi)
    : RenderMesh(rhi)
{

}

void VulkanMesh::Initalize()
{
    VulkanRHI* RenderRHI = static_cast<VulkanRHI*>(RHI);

    RenderRHI->Buffers->CreateMeshBuffers(this);

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

    vkCmdDrawIndexed(renderRHI->CommandBuffers->commandBuffers[commandBuffersIndex], static_cast<uint32_t>(Indices.size()), 1, 0, 0, 0);
}
