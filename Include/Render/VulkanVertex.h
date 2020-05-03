
#ifndef __UPSILON_RENDER_VULKANVERTEX_H__
#define __UPSILON_RENDER_VULKANVERTEX_H__

#include "Vertex.h"

#include <array>

#include <vulkan/vulkan.h>

class VulkanVertex : public Vertex
{

// Constructors
public:
    VulkanVertex();

// Variables
public:


// Methods
public:
    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

#endif // __UPSILON_RENDER_VULKANVERTEX_H__
