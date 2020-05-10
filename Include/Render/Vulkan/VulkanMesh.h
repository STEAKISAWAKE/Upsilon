
#ifndef __UPSILON_RENDER_VULKANMESH_H__
#define __UPSILON_RENDER_VULKANMESH_H__

#include "RenderMesh.h"

#include "vulkan/vulkan.h"

#include "Vulkan/VulkanCameraUniformBuffer.h"

class RenderRHI;

class VulkanDescriptorSets;

class VulkanMesh
    : public RenderMesh
{

public:
    VulkanMesh(RenderRHI* rhi);

public:
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;

    VulkanCameraUniformBuffer CUB;
    VulkanDescriptorSets* descriptorSets;
    

public:
    void Initalize() override;
    void Cleanup() override;
    
    void Draw(int info) override;

    void InitalizeUniformBuffers();
    void CleanupUniformBuffers();

    void InitalizeDescriptorSets();
    void CleanupDescriptorSets();

    void UpdateUniformBuffers(int imageIndex);

};

#endif __UPSILON_RENDER_VULKANMESH_H__
