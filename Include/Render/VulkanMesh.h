#ifndef __UPSILON_RENDER_VULKANMESH_H__
#define __UPSILON_RENDER_VULKANMESH_H__

#include "RenderMesh.h"
#include "VulkanVertex.h"

class VulkanRenderRHI;

class VulkanMesh : public RenderMesh
{

// Constructors
public:
    VulkanMesh();
    VulkanMesh(VulkanRenderRHI* vulkanRHI);


// Variables
public:
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformAllocations;

    std::vector<VkDescriptorSet> descriptorSets;

// Methods
public:
    void Initalize() override;
    void CreateDescriptorSets();
    void Cleanup() override;

    void Draw(int commandBufferIndex) override;

    void CleanupUniformBuffers() override;
    void InitalizeUniformBuffers() override;


// Methods
private:


};

#endif // __UPSILON_RENDER_VULKANMESH_H__