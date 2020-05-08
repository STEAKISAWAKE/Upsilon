#ifndef __UPSILON_RENDER_SHADER_H__
#define __UPSILON_RENDER_SHADER_H__

#include <vector>
#include <string>

#include <rttr/registration>

class RenderRHI;

class Shader
{

RTTR_ENABLE()

// Constructors
public:
    Shader();
    Shader(RenderRHI* renderRHI, std::vector<char> byteCode);

// Variables
public:
    RenderRHI* rhi;

    std::vector<char> Code;

// Methods
public:
    virtual void Initalize();
    virtual void Cleanup();

// Variables
private:


// Methods
private:



};

struct ShaderVertFrag
{
    Shader *vert;
    Shader *frag;
};

#endif // __UPSILON_RENDER_SHADER_H__