
#ifndef __UPSILON_RENDER_VULKANSURFACE_H__
#define __UPSILON_RENDER_VULKANSURFACE_H__

#include "vulkan/vulkan.h"

class VulkanInstance;
class Render;

class VulkanSurface
{

public:
    VulkanSurface(VulkanInstance* instance, Render* window);

public:
    VkSurfaceKHR surface;

    VulkanInstance* Instance;
    Render* Renderer;

public:
    void Initalize();
    void Cleanup();



};

#endif // __UPSILON_RENDER_VULKANSURFACE_H__
