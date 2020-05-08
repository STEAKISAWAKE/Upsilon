#include "RenderRHI.h"

#include <fstream>

#include <rttr/registration>

#include "Render.h"

#include "Shader.h"
#include "Log.h"

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<RenderRHI>("RenderRHI")
        .constructor<>()
        .constructor<Render*>()
        
        .method("Initalize", &RenderRHI::Initalize)
        .method("Cleanup", &RenderRHI::Cleanup)

        .method("LoadShader", &RenderRHI::LoadShader)
        .method("CreateShader", &RenderRHI::CreateShader);
    ; 
}

RenderRHI::RenderRHI()
{

}

RenderRHI::RenderRHI(Render* renderer)
{
    Renderer = renderer;
}

RenderRHI::~RenderRHI()
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

ShaderPool* RenderRHI::CreateShaderPool()
{
    return nullptr;
}

Shader* RenderRHI::CreateShader(int shaderIndex, ShaderType type, const std::vector<char>& code)
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

// Structures

void ShaderPool::Initalize()
{
    vertexShader->Initalize();
    fragmentShader->Initalize();
}

void ShaderPool::Cleanup(bool everything)
{
    vertexShader->Cleanup();
    fragmentShader->Cleanup();
}

bool ShaderPool::Filled()
{
    if (vertexShader && fragmentShader)
    {
        return true;
    }

    return false;
}