#ifndef __UPSILON_RENDER_RENDERRHI_H__
#define __UPSILON_RENDER_RENDERRHI_H__

#include <map>

#include <rttr/registration>

class Render;
class Shader;
class RenderMesh;

class RenderRHI
{

RTTR_ENABLE()

// Constructors
public:

    RenderRHI();

// Variables
public:
    Render* render;

    std::vector<std::pair<Shader*, Shader*>> shaders;
    std::vector<RenderMesh*> meshs;


// Methods
public:
    virtual void Initalize() {};
    virtual void Cleanup() {};

    virtual void DrawFrame() {};

    static std::vector<char> LoadShader(const std::string& filename);

    virtual Shader*     CreateShader();
    virtual RenderMesh* CreateMesh();

};

#endif // __UPSILON_RENDER_RENDERRHI_H__