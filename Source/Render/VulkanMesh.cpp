#include "VulkanMesh.h"

#include "VulkanRenderRHI.h"
#include "Log.h"

// Constructors

VulkanMesh::VulkanMesh()
{

}

VulkanMesh::VulkanMesh(VulkanRenderRHI* render)
{

}


// Methods

void VulkanMesh::Initalize()
{

    CreateVertexBuffer();
    CreateIndexBuffer();

}

void VulkanMesh::Cleanup()
{
    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);

    vkDestroyBuffer(renderRHI->device, indexBuffer, nullptr);
    vkFreeMemory(renderRHI->device, indexBufferMemory, nullptr);

    vkDestroyBuffer(renderRHI->device, vertexBuffer, nullptr);
    vkFreeMemory(renderRHI->device, vertexBufferMemory, nullptr);

}

void VulkanMesh::Draw(int commandBufferIndex)
{

    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);

    vkCmdBindPipeline(renderRHI->commandBuffers[commandBufferIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, renderRHI->graphicsPipelines[0]);

    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(renderRHI->commandBuffers[commandBufferIndex], 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(renderRHI->commandBuffers[commandBufferIndex], indexBuffer, 0, VK_INDEX_TYPE_UINT16);

    vkCmdDrawIndexed(renderRHI->commandBuffers[commandBufferIndex], static_cast<uint32_t>(Indices.size()), 1, 0, 0, 0);
}

void VulkanMesh::CreateVertexBuffer()
{
    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);

    VkDeviceSize bufferSize = sizeof(Vertices[0]) * Vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    renderRHI->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(renderRHI->device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, Vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(renderRHI->device, stagingBufferMemory);

    renderRHI->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

    renderRHI->CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(renderRHI->device, stagingBuffer, nullptr);
    vkFreeMemory(renderRHI->device, stagingBufferMemory, nullptr);

}

void VulkanMesh::CreateIndexBuffer()
{
    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);

    VkDeviceSize bufferSize = sizeof(Indices[0]) * Indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    renderRHI->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(renderRHI->device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, Indices.data(), (size_t) bufferSize);
    vkUnmapMemory(renderRHI->device, stagingBufferMemory);

    renderRHI->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    renderRHI->CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

    vkDestroyBuffer(renderRHI->device, stagingBuffer, nullptr);
    vkFreeMemory(renderRHI->device, stagingBufferMemory, nullptr);
}