#ifndef __UPSILON_RENDER_RENDERRHI_H__
#define __UPSILON_RENDER_RENDERRHI_H__

#include <map>

#include <rttr/registration>

class Render;
class Shader;
class Texture;
class RenderMesh;

class ShaderPool;

enum ShaderType
{
    E_ShaderTypeMin,
    E_VertexShader,
    E_FragmentShader,
    E_ShaderTypeMax
};

class RenderRHI
{

RTTR_ENABLE()

public:
    RenderRHI();
    RenderRHI(Render* render);
    ~RenderRHI();

public:
    Render* Renderer;

    size_t currentFrame = 0;

public:
    virtual void Initalize() {};
    virtual void Cleanup() {};

    virtual void InitalizeMeshes() {};
    virtual void CleanupMeshes() {};

    virtual void InitalizeShaders() {};
    virtual void CleanupShaders(bool everything) {};

    virtual void RecreateSwapChain() {};

    virtual void DrawFrame() {};

    virtual void FramebufferResized() {};

public:
    virtual ShaderPool* CreateShaderPool();
    virtual Shader*     CreateShader(int shaderIndex, ShaderType type, const std::vector<char>& code);
    virtual RenderMesh* CreateMesh();
    virtual Texture*    CreateTexture();

    static std::vector<char> LoadShader(const std::string& filename);

public:
    std::vector<ShaderPool*> ShaderPools;
    std::vector<RenderMesh*> Meshes;

};

/* A handle for the graphics pipeline shaders */
class ShaderPool
{

public:
    ShaderPool() {};

public:
    Shader* vertexShader = nullptr;
    Shader* fragmentShader = nullptr;

    virtual void Initalize();
    virtual void Cleanup(bool everything);

    virtual bool Filled();
};

#endif // __UPSILON_RENDER_RENDERRHI_H__