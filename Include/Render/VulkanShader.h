
#ifndef __UPSILON_RENDER_VULKANSHADER_H__
#define __UPSILON_RENDER_VULKANSHADER_H__

#include "Shader.h"

#include "vulkan/vulkan.h"

class VulkanShader : public Shader
{

// Constructors
public:
    VulkanShader();


// Variables
public:
    VkShaderModule shaderModule;


// Methods
public:
    void Initalize();
    void Cleanup();

};


#endif // __UPSILON_RENDER_VULKANSHADER_H__
