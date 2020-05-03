#include "RenderRHI.h"

#include <fstream>

#include <rttr/registration>

#include "Shader.h"
#include "Log.h"

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<RenderRHI>("RenderRHI")
        .constructor<>()
        
        .method("Initalize", &RenderRHI::Initalize)
        .method("Cleanup", &RenderRHI::Cleanup)

        .method("LoadShader", &RenderRHI::LoadShader)
        .method("CreateShader", &RenderRHI::CreateShader);
    ; 

}

RenderRHI::RenderRHI()
{
    
}

std::vector<char> RenderRHI::LoadShader(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        ULogError("Vulkan Shader", "Could not open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

Shader* RenderRHI::CreateShader(int shaderIndex, ShaderType type)
{
    return nullptr;
}

RenderMesh* RenderRHI::CreateMesh()
{
    return nullptr;
}

Texture* RenderRHI::CreateTexture()
{
    return nullptr;
}

int RenderRHI::GetLatestShaderIndex()
{
    bool filled = false;;

    if (shaders.size() != 0)
        filled = shaders[shaders.size() - 1].Filled();

    if (shaders.size() == 0 || filled)
        shaders.resize(shaders.size() + 1);

    return shaders.size() - 1;
}

// Structures

void GraphicsShaders::Initalize()
{
    vertexShader->Initalize();
    fragmentShader->Initalize();
}

void GraphicsShaders::Cleanup()
{
    vertexShader->Cleanup();
    fragmentShader->Cleanup();
}

bool GraphicsShaders::Filled()
{
    if (vertexShader && fragmentShader)
    {
        return true;
    }

    return false;
}