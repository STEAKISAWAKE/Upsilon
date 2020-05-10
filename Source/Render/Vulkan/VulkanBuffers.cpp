#include "VulkanBuffers.h"

#include "Vulkan/VulkanPhysicalDevice.h"
#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanCommandPool.h"
#include "Vulkan/VulkanMesh.h"

#include "Log.h"

VulkanBuffers::VulkanBuffers(VulkanPhysicalDevice* physicalDevice, VulkanDevice* device, VulkanSwapChain* swapChain, VulkanCommandPool* commandPool)
{
    PhysicalDevice = physicalDevice;
    Device = device;
    SwapChain = swapChain;
    CommandPool = commandPool;
}

void VulkanBuffers::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(Device->device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(Device->device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(Device->device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(Device->device, buffer, bufferMemory, 0);
}

void VulkanBuffers::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
     VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = CommandPool->commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(Device->device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(Device->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(Device->graphicsQueue);

    vkFreeCommandBuffers(Device->device, CommandPool->commandPool, 1, &commandBuffer);
}

void VulkanBuffers::CreateMeshBuffers(VulkanMesh* mesh)
{
    CreateIndexBuffer(mesh);
    CreateVertexBuffer(mesh);
}

void VulkanBuffers::CreateVertexBuffer(VulkanMesh* mesh)
{
    VkDeviceSize bufferSize = sizeof(mesh->Vertices[0]) * mesh->Vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(Device->device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, mesh->Vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(Device->device, stagingBufferMemory);

    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mesh->vertexBuffer, mesh->vertexBufferMemory);

    CopyBuffer(stagingBuffer, mesh->vertexBuffer, bufferSize);

    vkDestroyBuffer(Device->device, stagingBuffer, nullptr);
    vkFreeMemory(Device->device, stagingBufferMemory, nullptr);
}

void VulkanBuffers::CreateIndexBuffer(VulkanMesh* mesh)
{
    VkDeviceSize bufferSize = sizeof(mesh->Indices[0]) * mesh->Indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(Device->device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, mesh->Indices.data(), (size_t) bufferSize);
    vkUnmapMemory(Device->device, stagingBufferMemory);

    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mesh->indexBuffer, mesh->indexBufferMemory);

    CopyBuffer(stagingBuffer, mesh->indexBuffer, bufferSize);

    vkDestroyBuffer(Device->device, stagingBuffer, nullptr);
    vkFreeMemory(Device->device, stagingBufferMemory, nullptr);
}

void VulkanBuffers::CreateUniformBuffers(VulkanMesh* mesh)
{
    VkDeviceSize bufferSize = sizeof(CameraUniformBuffer);

    mesh->uniformBuffers.resize(SwapChain->swapChainImages.size());
    mesh->uniformBuffersMemory.resize(SwapChain->swapChainImages.size());

    for(size_t i = 0;  i < SwapChain->swapChainImages.size(); i++)
    {
        CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, mesh->uniformBuffers[i], mesh->uniformBuffersMemory[i]);
    }
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

