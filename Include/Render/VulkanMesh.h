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

// Methods
public:
    void Initalize() override;
    void Cleanup() override;

    void Draw(int commandBufferIndex) override;

    VkBuffer GetVertexBuffer() {return vertexBuffer;}
    VkBuffer GetIndexBuffer() {return indexBuffer;}

// Methods
private:
    void CreateVertexBuffer();
    void CreateIndexBuffer();

};

#endif // __UPSILON_RENDER_VULKANMESH_H__