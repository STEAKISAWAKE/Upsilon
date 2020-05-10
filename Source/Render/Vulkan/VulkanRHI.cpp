#include "VulkanRHI.h"

#include "Render.h"
#include "RenderWindow.h"

#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanDebugCallback.h"
#include "Vulkan/VulkanSurface.h"
#include "Vulkan/VulkanPhysicalDevice.h"
#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanImageViews.h"
#include "Vulkan/VulkanDescriptorLayout.h"
#include "Vulkan/VulkanDescriptorPool.h"
#include "Vulkan/VulkanShader.h"
#include "Vulkan/VulkanGraphicsPipeline.h"
#include "Vulkan/VulkanRenderPass.h"
#include "Vulkan/VulkanFramebuffers.h"
#include "Vulkan/VulkanCommandPool.h"
#include "Vulkan/VulkanCommandBuffers.h"
#include "Vulkan/VulkanSemaphores.h"
#include "Vulkan/VulkanBuffers.h"
#include "Vulkan/VulkanMesh.h"

#include "Log.h"

VulkanRHI::VulkanRHI()
{

}

VulkanRHI::VulkanRHI(Render* renderer)
{
    Renderer = renderer;

    Instance = new VulkanInstance();
    DebugCallback = new VulkanDebugCallback(Instance);
    Surface = new VulkanSurface(Instance, Renderer);
    PhysicalDevice = new VulkanPhysicalDevice(Instance, Surface);
    Device = new VulkanDevice(PhysicalDevice);
    SwapChain = new VulkanSwapChain(&Renderer->Window, PhysicalDevice, Device, Surface);
    DescriptorLayout = new VulkanDescriptorLayout(Device);
    DescriptorPool = new VulkanDescriptorPool(Device, SwapChain);
    ImageViews = new VulkanImageViews(Device, SwapChain);
    CommandPool = new VulkanCommandPool(Device, PhysicalDevice);
    Buffers = new VulkanBuffers(PhysicalDevice, Device, SwapChain, CommandPool);
    RenderPass = new VulkanRenderPass(Device, SwapChain);
    Framebuffers = new VulkanFramebuffers(Device, SwapChain, RenderPass);


    ShaderPools.push_back(CreateShaderPool()); // We must have at least one shader pool

    CommandBuffers = new VulkanCommandBuffers(this);
    Semaphores = new VulkanSemaphores(Device, SwapChain);

}

VulkanRHI::~VulkanRHI()
{
    delete Buffers;
    delete Semaphores;
    delete CommandBuffers;
    delete CommandPool;
    delete Framebuffers;
    delete RenderPass;
    delete ImageViews;
    delete SwapChain;
    delete Device;
    delete PhysicalDevice;
    delete DebugCallback;
    delete Instance;
}

void VulkanRHI::Initalize()
{
    Instance->Initalize();
    DebugCallback->Initalize();
    Surface->Initalize();
    PhysicalDevice->PickPhysicalDevice();
    Device->Initalize();
    SwapChain->Initalize();
    ImageViews->Initalize();
    RenderPass->Initalize();
    DescriptorLayout->Initalize();
    InitalizeMeshUniformBuffers();
    DescriptorPool->Initalize();
    InitalizeMeshDescriptorSets();
    InitalizeShaders(); // Also creates graphics pipeline


    Framebuffers->Initalize();
    CommandPool->Initalize();
    InitalizeMeshes();
    CommandBuffers->Initalize();
    Semaphores->Initalize();
}

void VulkanRHI::Cleanup()
{   
    vkDeviceWaitIdle(Device->device);

    CleanupSwapChain();

    DescriptorLayout->Cleanup();
    CleanupMeshes();
    Semaphores->Cleanup();
    CommandPool->Cleanup();
    Device->Cleanup();
    DebugCallback->Cleanup();
    Surface->Cleanup();
    Instance->Cleanup();
}

void VulkanRHI::InitalizeMeshes()
{
    for(auto mesh : Meshes)
    {
        mesh->Initalize();
    }
}

void VulkanRHI::InitalizeMeshUniformBuffers()
{
    for(auto mesh : Meshes)
    {
        static_cast<VulkanMesh*>(mesh)->InitalizeUniformBuffers();
    }
}

void VulkanRHI::InitalizeMeshDescriptorSets()
{
    for(auto mesh : Meshes)
    {
        static_cast<VulkanMesh*>(mesh)->InitalizeDescriptorSets();
    }
}

void VulkanRHI::CleanupMeshes()
{
    for(auto mesh : Meshes)
    {
        mesh->Cleanup();
    }
}

void VulkanRHI::CleanupMeshUniformBuffers()
{
    for(auto mesh : Meshes)
    {
        static_cast<VulkanMesh*>(mesh)->CleanupUniformBuffers();
    }
}

void VulkanRHI::CleanupMeshDescriptorSets()
{
    for(auto mesh : Meshes)
    {
        static_cast<VulkanMesh*>(mesh)->CleanupDescriptorSets();
    }
}

void VulkanRHI::InitalizeShaders()
{
    for(auto shaderGroup : ShaderPools)
    {
        shaderGroup->Initalize();
    }
}

void VulkanRHI::CleanupShaders(bool everything)
{
    for(auto shaderGroup : ShaderPools)
    {
        shaderGroup->Cleanup(everything);
    }
}


void VulkanRHI::RecreateSwapChain()
{

    int width = 0, height = 0;
    Renderer->Window.GetFramebufferSize(width, height);
    while(width == 0 || height == 0)
    {
        Renderer->Window.GetFramebufferSize(width, height);
        glfwWaitEvents();
    }


    vkDeviceWaitIdle(Device->device);

    CleanupSwapChain();
    SwapChain->Initalize();
    ImageViews->Initalize();
    RenderPass->Initalize();
    InitalizeShaders();
    Framebuffers->Initalize();
    InitalizeMeshUniformBuffers();
    DescriptorPool->Initalize();
    InitalizeMeshDescriptorSets();
    
    CommandBuffers->Initalize();
}

void VulkanRHI::CleanupSwapChain()
{
    Framebuffers->Cleanup();
    CommandBuffers->Cleanup();
    CleanupShaders(true);
    RenderPass->Cleanup();
    ImageViews->Cleanup();
    SwapChain->Cleanup();
    CleanupMeshUniformBuffers();
    DescriptorPool->Cleanup();
    CleanupMeshDescriptorSets();
}

void VulkanRHI::DrawFrame()
{
    vkWaitForFences(Device->device, 1, &Semaphores->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);


    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(Device->device, SwapChain->swapChain, UINT64_MAX, Semaphores->imageAvailableSemaphore[currentFrame], VK_NULL_HANDLE, &imageIndex);

    if(result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        RecreateSwapChain();
        return;
    }
    else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        ULogError("Vulkan Draw Frame", "Could not aquire swap chain image!");
    }

    if(Semaphores->imagesInFlight[imageIndex] != VK_NULL_HANDLE)
    {
        vkWaitForFences(Device->device, 1, &Semaphores->imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }

    Semaphores->imagesInFlight[imageIndex] = Semaphores->inFlightFences[currentFrame];

    UpdateUniformBuffers(imageIndex);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    
    VkSemaphore waitSemaphores[] = {Semaphores->imageAvailableSemaphore[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &CommandBuffers->commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = {Semaphores->renderFinishedSemaphore[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(Device->device, 1, &Semaphores->inFlightFences[currentFrame]);

    if(vkQueueSubmit(Device->graphicsQueue, 1, &submitInfo, Semaphores->inFlightFences[currentFrame]) != VK_SUCCESS)
    {
        ULogError("Vulkan Draw Frame", "Could not submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {SwapChain->swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr;

    result = vkQueuePresentKHR(Device->presentQueue, &presentInfo);

    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized)
    {
        RecreateSwapChain();
    }
    else if(result != VK_SUCCESS)
    {
        ULogError("Vulkan Render Frame", "Could not present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % VulkanDevice::MAX_FRAMES_IN_FLIGHT;
    vkQueueWaitIdle(Device->presentQueue);
}

void VulkanRHI::UpdateUniformBuffers(int imageIndex)
{
    for(auto mesh : Meshes)
    {
        auto vkMesh = static_cast<VulkanMesh*>(mesh);



        void* data;
        vkMapMemory(Device->device, vkMesh->uniformBuffersMemory[imageIndex], 0, sizeof(vkMesh->CUB), 0, &data);
            memcpy(data, &vkMesh->CUB, sizeof(vkMesh->CUB));
        vkUnmapMemory(Device->device, vkMesh->uniformBuffersMemory[imageIndex]);
    }
}

ShaderPool* VulkanRHI::CreateShaderPool()
{
    return new VulkanShaderPool(Device, SwapChain, DescriptorLayout, RenderPass);
}

Shader* VulkanRHI::CreateShader(int shaderIndex, ShaderType type, const std::vector<char>& code)
{


    if(shaderIndex != 0 && ShaderPools.size() - 1 > shaderIndex)
    {
        ULogError("Vulkan RHI", "Can not create a shader that is larger that the shaders array size!"); return nullptr;
    }

    if(ShaderPools.size() == 0 || ShaderPools[ShaderPools.size() - 1]->Filled())
    {
        ShaderPools.push_back(CreateShaderPool());
    }

    if(ShaderPools[shaderIndex]->Filled())
    {
        ULogError("Vulkan RHI", "Can not add shader to a GraphicsShadersObject that is already full!"); return nullptr;
    }

    if(type > E_ShaderTypeMax - 1 || type < E_ShaderTypeMin + 1)
    {
        ULogError("Vulkan RHI", "Could not create a shader of undefined type!"); return nullptr;
    }

    
    Shader* newShader = new VulkanShader(Device, code);

    switch (type)
    {
        case E_VertexShader:
            ShaderPools[shaderIndex]->vertexShader = newShader;
            break;

        case E_FragmentShader:
            ShaderPools[shaderIndex]->fragmentShader = newShader;
            break;

        default:
            ULogError("Vulkan RHI", "Could not create a vulkan shader of unknown type!");
    }



    return newShader;
}

RenderMesh* VulkanRHI::CreateMesh()
{
    RenderMesh* newMesh = new VulkanMesh(this);

    return newMesh;
}

void VulkanRHI::FramebufferResized()
{
    framebufferResized = true;
}

// VulkanGraphicsShaders class

VulkanShaderPool::VulkanShaderPool(VulkanDevice* device, VulkanSwapChain* swapChain, VulkanDescriptorLayout* descriptorLayout, VulkanRenderPass* renderPass)
{
    Device = device;
    SwapChain = swapChain;
    DescriptorLayout = descriptorLayout;
    RenderPass = renderPass;
    

    GraphicsPipeline = new VulkanGraphicsPipeline(Device, SwapChain, DescriptorLayout, RenderPass, this);
}

void VulkanShaderPool::Initalize()
{

    vertexShader->Initalize();
    fragmentShader->Initalize();

    GraphicsPipeline->Initalize();

    Cleanup(false);
}

void VulkanShaderPool::Cleanup(bool everything)
{
    if(!everything && Filled())
    {
        fragmentShader->Cleanup();
        vertexShader->Cleanup();
    }

    if(everything && GraphicsPipeline != nullptr)
    {
        GraphicsPipeline->Cleanup();
    }
}


