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

// Constructors
public:

    RenderRHI();

// Variables
public:
    Render* render;

    std::vector<GraphicsShaders> shaders;
    std::vector<RenderMesh*> meshes;
    std::vector<Texture*> textures;


// Methods
public:

    // Initalize
    virtual void Initalize() {};
    virtual void InitalizeShaders() {};
    virtual void InitalizeMeshes() {};
    virtual void InitalizeMeshUniformBuffers() {};

    // Draw
    virtual void DrawFrame() {};
    virtual void UpdateUniformBuffers(uint32_t info) {};
    virtual void DrawMeshes() {};
    
    // Cleanup
    virtual void Cleanup() {};
    virtual void CleanupShaders() {};
    virtual void CleanupMeshes() {};
    virtual void CleanupMeshUniformBuffers() {};

    // Create Render Specific Objects
    virtual Shader*     CreateShader(int shaderIndex, ShaderType type);
    virtual RenderMesh* CreateMesh();
    virtual Texture* CreateTexture();

    // Utils
    static std::vector<char> LoadShader(const std::string& filename);

    virtual int GetLatestShaderIndex();

};

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