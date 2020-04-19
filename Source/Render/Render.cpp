#include "Render.h"

#include <GLFW/glfw3.h>

#include "VulkanRenderRHI.h"
#include "Log.h"



RTTR_REGISTRATION
{
    using namespace rttr;
    
    registration::enumeration<E_RHITypes>("E_RHITypes")
        (
            value("VulkanRHI", E_RHITypes::VulkanRHI),
            value("OpenGLRHI", E_RHITypes::OpenGLRHI)
        );

    registration::class_<Render>("Render")
        .constructor<>()
        .constructor<E_RHITypes>()

        .property("RHI", &Render::RHI)
        
        .method("Initalize", &Render::Initalize)
        .method("Cleanup", &Render::Cleanup)
        .method("SwitchRHI", &Render::SwitchRHI)
    ;
}

Render::Render()
{
    if(!glfwInit())
    {
        Log("Render Initalization", "Could not initalize glfw!");
    }

    // Create Vulkan RHI as a default
    RHI = new VulkanRenderRHI();

}


Render::Render(E_RHITypes RHIType) : Render() // Call glfwInit
{   
    // This constructor reallocates RHI variable to different type
    delete RHI;

    switch(RHIType)
    {
        case VulkanRHI:
            RHI = new VulkanRenderRHI();
            break;
        
        case OpenGLRHI:
            // RHI = new OpenGLRenderRHI();
            break;
    }
}