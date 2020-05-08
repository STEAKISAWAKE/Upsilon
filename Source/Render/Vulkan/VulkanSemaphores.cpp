#include "Vulkan/VulkanSemaphores.h"

#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanSwapChain.h"

#include "Log.h"

VulkanSemaphores::VulkanSemaphores(VulkanDevice* device, VulkanSwapChain* swapChain)
{
    Device = device;
    SwapChain = swapChain;
}

void VulkanSemaphores::Initalize()
{
    imageAvailableSemaphore.resize(VulkanDevice::MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphore.resize(VulkanDevice::MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(VulkanDevice::MAX_FRAMES_IN_FLIGHT);
    imagesInFlight.resize(SwapChain->swapChainImages.size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for(size_t i = 0; i < VulkanDevice::MAX_FRAMES_IN_FLIGHT; i++)
    {
        if(vkCreateSemaphore(Device->device, &semaphoreInfo, nullptr, &imageAvailableSemaphore[i]) != VK_SUCCESS ||
           vkCreateSemaphore(Device->device, &semaphoreInfo, nullptr, &renderFinishedSemaphore[i]) != VK_SUCCESS ||
           vkCreateFence(Device->device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
        {
            ULogError("Vulkan Semaphore", "Could not create semaphores!");
        }
    }
}

void VulkanSemaphores::Cleanup()
{
    for(size_t i = 0; i < VulkanDevice::MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore(Device->device, renderFinishedSemaphore[i], nullptr);
        vkDestroySemaphore(Device->device, imageAvailableSemaphore[i], nullptr);
        vkDestroyFence(Device->device, inFlightFences[i], nullptr);
    }
}

