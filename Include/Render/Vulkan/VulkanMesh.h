
#ifndef __UPSILON_RENDER_VULKANMESH_H__
#define __UPSILON_RENDER_VULKANMESH_H__

#include "RenderMesh.h"

#include "vulkan/vulkan.h"

class VulkanMesh
    : public RenderMesh
{

public:
    VulkanMesh(RenderRHI* rhi);

    void Initalize() override;
    void Cleanup() override;
    
    void Draw(int info) override;

public:
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

};

#endif __UPSILON_RENDER_VULKANMESH_H__
