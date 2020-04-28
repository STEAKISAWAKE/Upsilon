#include "RenderMesh.h"

#include "RenderRHI.h"

// Constructors
RenderMesh::RenderMesh()
{

}

RenderMesh::RenderMesh(RenderRHI* renderRHI)
{
    rhi = renderRHI;
    rhi->meshs.push_back(this);
}

// Methods
void RenderMesh::Draw(int info)
{

}

void RenderMesh::Initalize()
{

}

void RenderMesh::Cleanup()
{
    
}