#ifndef __UPSILON_RENDER_RENDER_H__
#define __UPSILON_RENDER_RENDER_H__

#include <rttr/registration>

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

// Methods
public:
    void Initalize();
    void Cleanup();

    void SwitchRHI(E_RHITypes RHIType);


};

#endif // __UPSILON_RENDER_RENDER_H__