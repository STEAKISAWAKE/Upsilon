#include "Vulkan/VulkanSurface.h"

#include <GLFW/glfw3.h>

#include "Render.h"
#include "Vulkan/VulkanRHI.h"

#include "Vulkan/VulkanInstance.h"

#include "Log.h"

VulkanSurface::VulkanSurface(VulkanRHI* rhi)
{
    RHI = rhi;
}

void VulkanSurface::Initalize()
{
    if(glfwCreateWindowSurface(RHI->Instance->instance, RHI->Renderer->Window.glfwWin, nullptr, &surface) != VK_SUCCESS)
    {
        ULog("Vulkan Surface", "Could not create window surface!");
    }
}

void VulkanSurface::Cleanup()
{
    vkDestroySurfaceKHR(RHI->Instance->instance, surface, nullptr);
}
