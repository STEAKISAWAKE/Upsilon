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
    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);

    renderRHI->CreateVertexBuffer(this);
    renderRHI->CreateIndexBuffer(this);


}

void VulkanMesh::Cleanup()
{
    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);

 

}

void VulkanMesh::Draw(int commandBufferIndex)
{

    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);




}

void VulkanMesh::CleanupUniformBuffers()
{
    
}

void VulkanMesh::InitalizeUniformBuffers()
{
    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);


    renderRHI->CreateUniformBuffers(this);
    renderRHI->CreateDescriptorSets(this);
}