
#ifndef __UPSILON_RENDER_SHADER_H__
#define __UPSILON_RENDER_SHADER_H__

#include <vector>
#include <string>

#include <rttr/registration>

class RenderRHI;

/* CLASS INFO

Shader's should be created before the Render RHI is initalized.

*/


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

    std::vector<char> spirvByteCode;

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

