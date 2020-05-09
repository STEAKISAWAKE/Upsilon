
#ifndef __UPSILON_RENDER_VULKANBUFFERS_H__
#define __UPSILON_RENDER_VULKANBUFFERS_H__

#include "vulkan/vulkan.h"

class VulkanPhysicalDevice;
class VulkanDevice;
class VulkanCommandPool;
class VulkanMesh;

class VulkanBuffers
{

public:
    VulkanBuffers(VulkanPhysicalDevice* physicalDevice, VulkanDevice* device, VulkanCommandPool* commandPook);

public:
    VulkanPhysicalDevice* PhysicalDevice;
    VulkanDevice* Device;
    VulkanCommandPool* CommandPool;

public:
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void CreateMeshBuffers(VulkanMesh* mesh);
    void CreateVertexBuffer(VulkanMesh* mesh);
    void CreateIndexBuffer(VulkanMesh* mesh);

    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

};

#endif // __UPSILON_RENDER_VULKANBUFFERS_H__
