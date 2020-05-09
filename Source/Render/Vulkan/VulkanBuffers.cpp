#include "VulkanBuffers.h"

#include "VulkanPhysicalDevice.h"
#include "VulkanDevice.h"
#include "VulkanMesh.h"

#include "Log.h"

VulkanBuffers::VulkanBuffers(VulkanPhysicalDevice* physicalDevice, VulkanDevice* device)
{
    PhysicalDevice = physicalDevice;
    Device = device;
}

void VulkanBuffers::CreateMeshBuffers(VulkanMesh* mesh)
{
    CreateVertexBuffer(mesh);
}

void VulkanBuffers::CreateVertexBuffer(VulkanMesh* mesh)
{
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(mesh->Vertices[0]) * mesh->Vertices.size();
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateBuffer(Device->device, &bufferInfo, nullptr, &mesh->vertexBuffer) != VK_SUCCESS)
    {
        ULogError("Vulkan Buffers", "Could not create a vertex buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(Device->device, mesh->vertexBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if(vkAllocateMemory(Device->device, &allocInfo, nullptr, &mesh->vertexBufferMemory) != VK_SUCCESS)
    {
        ULogError("Vulkan Buffers", "Could not allocate vertex buffer memory!");
    }

    vkBindBufferMemory(Device->device, mesh->vertexBuffer, mesh->vertexBufferMemory, 0);

    void* data;
    vkMapMemory(Device->device, mesh->vertexBufferMemory, 0, bufferInfo.size, 0, &data);
        memcpy(data, mesh->Vertices.data(), (size_t) bufferInfo.size);
    vkUnmapMemory(Device->device, mesh->vertexBufferMemory);

}

uint32_t VulkanBuffers::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(PhysicalDevice->physicalDevice, &memProperties);

    for(uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    ULogError("Vulkan Buffers", "Could not find suitable memory type!");
    return 0;
}

