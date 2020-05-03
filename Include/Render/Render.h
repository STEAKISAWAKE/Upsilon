#ifndef __UPSILON_RENDER_RENDER_H__
#define __UPSILON_RENDER_RENDER_H__

#include <rttr/registration>

#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>

class RenderRHI;

enum E_RHITypes
{
    VulkanRHI,
    OpenGLRHI
};

class Render
{

    RTTR_ENABLE()

// Constructors
public:

    Render();
    Render(E_RHITypes RHIType);

// Variables
public:

    RenderRHI* RHI;


    glm::mat4 camera;
    
    GLFWwindow* window;

// Methods
public:
    void Initalize();
    void Cleanup();

    void SwitchRHITo(E_RHITypes RHIType);


};

#endif // __UPSILON_RENDER_RENDER_H__