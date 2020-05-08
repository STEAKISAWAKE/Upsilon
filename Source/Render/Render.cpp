#include "Render.h"

#include "RenderWindow.h"
#include "Shader.h"

#include "VulkanRHI.h"

#include "Log.h"

RTTR_REGISTRATION
{
    using namespace rttr;
    
    registration::enumeration<E_RHITypes>("E_RHITypes")
        (
            value("VulkanRHI", E_RHITypes::E_VulkanRHI),
            value("OpenGLRHI", E_RHITypes::E_OpenGLRHI)
        );

    registration::class_<Render>("Render")
        .constructor<>()
        .constructor<E_RHITypes>()

        .property("RHI", &Render::RHI)
        
        .method("Initalize", &Render::Initalize)
        .method("Cleanup", &Render::Cleanup)
        .method("SwitchRHITo", &Render::SwitchRHITo)
    ;
}


Render::Render()
{
    if(!glfwInit())
    {
        ULog("Render Initalization", "Could not initalize glfw!");
    }

    // Create Vulkan RHI as a default
    RHI = new VulkanRHI(this);

}


Render::Render(E_RHITypes RHIType) : Render() // Call glfwInit
{   
    // This constructor reallocates RHI variable to different type
    delete RHI;

    switch(RHIType)
    {
        case E_VulkanRHI:
            RHI = new VulkanRHI(this);
            break;
        
        case E_OpenGLRHI:
            // RHI = new OpenGLRenderRHI();
            break;
    }

}


void Render::Initalize()
{   

    Window.CreateWindow("Upsilon");
    glfwSetWindowUserPointer(Window.glfwWin, RHI);

    RHI->Initalize();
}


void Render::Cleanup()
{
    RHI->Cleanup();

    Window.CloseWindow();
}


void Render::SwitchRHITo(E_RHITypes RHIType)
{
    RHI->Cleanup();
}