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

    if(!file.is_open())
    {
        ULogError("RHI Shader Loader", "Could not load shader file!");
        return std::vector<char>();
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

void RenderRHI::CreateShader(Shader* newShader)
{
        
}