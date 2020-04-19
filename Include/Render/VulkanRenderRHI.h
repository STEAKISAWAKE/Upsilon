#ifndef __UPSILON_RENDER_VULKANRENDERRHI_H__
#define __UPSILON_RENDER_VULKANRENDERRHI_H__

#include "RenderRHI.h"

#include <rttr/registration>

#include "vulkan/vulkan.h"

class VulkanRenderRHI 
    : public RenderRHI
{
    
    RTTR_ENABLE(RenderRHI)

// Constructors
public:
  
    VulkanRenderRHI();

// Variables
public:


// Methods
public:
    virtual void Initalize();
    virtual void Cleanup();


// Variables
private:
    VkInstance instance;

// Methods
private:
    void CreateInstance();



};

#endif // __UPSILON_RENDER_VULKANRENDERRHI_H__