#include "Render.h"

#include "Shader.h"

#include "VulkanRHI.h"

#include "Log.h"

VulkanRHI test;

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
    RHI = new VulkanRHI();
    RHI->render = this;

}


Render::Render(E_RHITypes RHIType) : Render() // Call glfwInit
{   
    // This constructor reallocates RHI variable to different type
    delete RHI;

    switch(RHIType)
    {
        case E_VulkanRHI:
            RHI = new VulkanRHI();
            break;
        
        case E_OpenGLRHI:
            // RHI = new OpenGLRenderRHI();
            break;
    }

    RHI->render = this;
}


void Render::Initalize()
{   
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(1920, 1080, "Upsilon", NULL, NULL);

    glfwSetWindowSizeLimits(window, 100, 100, -1, -1);

    RHI->Initalize();
}


void Render::Cleanup()
{
    RHI->Cleanup();

    glfwDestroyWindow(window);
}


void Render::SwitchRHITo(E_RHITypes RHIType)
{
    RHI->Cleanup();
}