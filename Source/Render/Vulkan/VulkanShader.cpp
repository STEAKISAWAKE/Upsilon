#include "VulkanShader.h"

#include "Vulkan/VulkanDevice.h"
#include "Log.h"

VulkanShader::VulkanShader(VulkanDevice* device, const std::vector<char>& code)
{
    Code = code;
    Device = device;
}

void VulkanShader::Initalize()
{
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = Code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(Code.data());

    if(vkCreateShaderModule(Device->device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        ULogError("Vulkan Shader", "Could not create shader module!");
    }
    
}

void VulkanShader::Cleanup()
{
    vkDestroyShaderModule(Device->device, shaderModule, nullptr);
}