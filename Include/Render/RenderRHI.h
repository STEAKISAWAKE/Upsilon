#ifndef __UPSILON_RENDER_RENDERRHI_H__
#define __UPSILON_RENDER_RENDERRHI_H__

#include <map>

#include <rttr/registration>

class Render;
class Shader;
class Texture;
class RenderMesh;

class GraphicsShaders;

enum ShaderType
{
    E_VertexShader,
    E_FragmentShader
};

class RenderRHI
{

RTTR_ENABLE()

public:

    RenderRHI();

public:
    Render* render;

public:

    // Initalize
    virtual void Initalize() {};
    virtual void ReInitalize() {};

    // Draw
    virtual void DrawFrame() {};
    
    // Cleanup
    virtual void Cleanup() {};

public:
    // Create Render Specific Objects
    virtual Shader*     CreateShader(int shaderIndex, ShaderType type);
    virtual RenderMesh* CreateMesh();
    virtual Texture* CreateTexture();

    // Utils
    static std::vector<char> LoadShader(const std::string& filename);

};

/* A handle for the graphics pipeline shaders */
class GraphicsShaders
{

public:
    GraphicsShaders() {};

public:
    Shader* vertexShader = nullptr;
    Shader* fragmentShader = nullptr;

    void Initalize();
    void Cleanup();

    bool Filled();
};

#endif // __UPSILON_RENDER_RENDERRHI_H__