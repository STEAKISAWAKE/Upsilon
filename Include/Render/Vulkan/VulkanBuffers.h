
#ifndef __UPSILON_RENDER_VULKANBUFFERS_H__
#define __UPSILON_RENDER_VULKANBUFFERS_H__

#include "vulkan/vulkan.h"

class VulkanRHI;

class VulkanMesh;

class VulkanBuffers
{

public:
    VulkanBuffers(VulkanRHI* rhi);

public:
    VulkanRHI* RHI;

public:
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void CreateMeshBuffers(VulkanMesh* mesh);
    void CreateVertexBuffer(VulkanMesh* mesh);
    void CreateIndexBuffer(VulkanMesh* mesh);
    void CreateUniformBuffers(VulkanMesh* mesh);

    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

};

#endif // __UPSILON_RENDER_VULKANBUFFERS_H__
