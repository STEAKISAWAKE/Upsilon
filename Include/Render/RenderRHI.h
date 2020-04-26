#ifndef __UPSILON_RENDER_RENDERRHI_H__
#define __UPSILON_RENDER_RENDERRHI_H__

#include <map>

#include <rttr/registration>

class Render;
class Shader;

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


// Methods
public:
    virtual void Initalize() {};
    virtual void Cleanup() {};

    virtual void DrawFrame() {};

    static std::vector<char> LoadShader(const std::string& filename);
    virtual void CreateShader(Shader* newShader);

};

#endif // __UPSILON_RENDER_RENDERRHI_H__