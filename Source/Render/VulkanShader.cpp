#include "VulkanShader.h"

#include "VulkanRenderRHI.h"
#include "Log.h"

VulkanShader::VulkanShader()
{


}

void VulkanShader::Initalize()
{
    Shader::Initalize();

    VulkanRenderRHI* renderRHI = static_cast<VulkanRenderRHI*>(rhi);

    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = spirvByteCode.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(spirvByteCode.data());

    if(vkCreateShaderModule(renderRHI->device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        ULogError("Vulkan Shader", "Could not create shader!");
    }
    
}

void VulkanShader::Cleanup()
{
    vkDestroyShaderModule(dynamic_cast<VulkanRenderRHI*>(rhi)->device, shaderModule, nullptr);
}