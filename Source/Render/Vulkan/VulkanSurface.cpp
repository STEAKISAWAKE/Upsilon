#include "Vulkan/VulkanSurface.h"

#include <GLFW/glfw3.h>

#include "Vulkan/VulkanInstance.h"
#include "Render.h"
#include "Log.h"

VulkanSurface::VulkanSurface(VulkanInstance* instance, Render* render)
{
    Instance = instance;
    Renderer = render;
}

void VulkanSurface::Initalize()
{
    if(glfwCreateWindowSurface(Instance->instance, Renderer->Window.glfwWin, nullptr, &surface) != VK_SUCCESS)
    {
        ULog("Vulkan Surface", "Could not create window surface!");
    }
}

void VulkanSurface::Cleanup()
{
    vkDestroySurfaceKHR(Instance->instance, surface, nullptr);
}
