#include "Shader.h"

#include <fstream>

#include "RenderRHI.h"
#include "Log.h"

// RTTR
RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Shader>("Shader")
        
        // Constructors
        .constructor<>()
        .constructor<RenderRHI*, std::vector<char>>();

        // Methods


}

// Constructors
Shader::Shader()
{

}

Shader::Shader(RenderRHI* renderRHI, std::vector<char> byteCode)
{
    rhi = renderRHI;
    spirvByteCode = byteCode;

    Initalize();

}

// Methods
void Shader::Initalize()
{
    // VulkanShader will do this
    // OpenGLShader will do this
}