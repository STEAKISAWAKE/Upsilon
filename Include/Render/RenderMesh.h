#ifndef __UPSILON_RENDER_RENDERMESH_H__
#define __UPSILON_RENDER_RENDERMESH_H__

#include "Mesh.h"

#include <string>

class RenderRHI;

class RenderMesh 
    : public Mesh
{

public:
    RenderMesh(RenderRHI* rhi);

public:
    RenderRHI* RHI;

public:
    virtual void Draw(int info);

    virtual void Initalize();
    virtual void Cleanup();

    virtual bool LoadMesh(std::string meshDir);

};

#endif // __UPSILON_RENDER_RENDERMESH_H__