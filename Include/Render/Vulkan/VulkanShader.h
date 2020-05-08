
#ifndef __UPSILON_RENDER_VULKANSHADER_H__
#define __UPSILON_RENDER_VULKANSHADER_H__

#include "Shader.h"

#include <vector>

#include "vulkan/vulkan.h"

class VulkanDevice;
class VulkanGraphicsPipeline;

class VulkanShader
    : public Shader
{

public:
    VulkanShader(VulkanDevice* device, const std::vector<char>& code);

public:
    VkShaderModule shaderModule;


    VulkanDevice* Device;

public:
    void Initalize() override;
    void Cleanup() override;


};

#endif // __UPSILON_RENDER_VULKANSHADER_H__
