#include "Render.h"

#include "Shader.h"
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
    RHI = new VulkanRenderRHI();
    RHI->render = this;
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
            // RHI = new OpenGLRenderRHI();/* code */
            break;
    }

    RHI->render = this;
}


void Render::Initalize()
{   
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


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