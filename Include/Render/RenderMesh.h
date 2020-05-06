#ifndef __UPSILON_RENDER_RENDERMESH_H__
#define __UPSILON_RENDER_RENDERMESH_H__

#include "Mesh.h"

#include <string>

#include "RenderUniformBuffer.h"

class RenderRHI;

class RenderMesh : public Mesh
{

// Constructors
public:
    RenderMesh();
    RenderMesh(RenderRHI* rhi); // Automatically adds mesh to rhi


// Variables
public:
    RenderRHI* rhi;

    RenderUniformBuffer uniformBuffer;


// Methods
public:
    virtual void Draw(int info);

    virtual void Initalize();
    virtual void Cleanup();

    virtual void InitalizeUniformBuffers() {};
    virtual void CleanupUniformBuffers() {};

    virtual bool LoadMesh(std::string meshDir);

};

#endif // __UPSILON_RENDER_RENDERMESH_H__