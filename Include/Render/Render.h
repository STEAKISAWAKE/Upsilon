#ifndef __UPSILON_RENDER_RENDER_H__
#define __UPSILON_RENDER_RENDER_H__

#include <rttr/registration>

#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>

class RenderRHI;

enum E_RHITypes
{
    E_VulkanRHI,
    E_OpenGLRHI
};

class Render
{

    RTTR_ENABLE()

public:

    Render();
    Render(E_RHITypes RHIType);

public:

    RenderRHI* RHI;
    GLFWwindow* window;

public:
    void Initalize();
    void Cleanup();

    void SwitchRHITo(E_RHITypes RHIType); // Runtime RHI switching.


};

#endif // __UPSILON_RENDER_RENDER_H__