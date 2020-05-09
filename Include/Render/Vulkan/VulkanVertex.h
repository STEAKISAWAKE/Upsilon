
#ifndef __UPSILON_RENDER_VULKANVERTEX_H__
#define __UPSILON_RENDER_VULKANVERTEX_H__

#include "Vertex.h"

#include <array>

#include "vulkan/vulkan.h"

class VulkanVertex2D
    : public Vertex2D
{

public:
    static VkVertexInputBindingDescription GetBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();

};  

#endif // __UPSILON_RENDER_VULKANVERTEX_H__
