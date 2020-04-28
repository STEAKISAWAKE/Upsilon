#ifndef __UPSILON_RENDER_RENDERMESH_H__
#define __UPSILON_RENDER_RENDERMESH_H__

#include "Mesh.h"

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


// Methods
public:
    virtual void Draw(int info);

    virtual void Initalize();
    virtual void Cleanup();


};

#endif // __UPSILON_RENDER_RENDERMESH_H__