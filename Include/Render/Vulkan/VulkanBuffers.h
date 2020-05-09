
#ifndef __UPSILON_RENDER_VULKANBUFFERS_H__
#define __UPSILON_RENDER_VULKANBUFFERS_H__

#include "vulkan/vulkan.h"

class VulkanPhysicalDevice;
class VulkanDevice;
class VulkanMesh;

class VulkanBuffers
{

public:
    VulkanBuffers(VulkanPhysicalDevice* physicalDevice, VulkanDevice* device);

public:
    VulkanPhysicalDevice* PhysicalDevice;
    VulkanDevice* Device;

public:
    void CreateMeshBuffers(VulkanMesh* mesh); // TODO
    void CreateVertexBuffer(VulkanMesh* mesh);
    
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

};

#endif // __UPSILON_RENDER_VULKANBUFFERS_H__
