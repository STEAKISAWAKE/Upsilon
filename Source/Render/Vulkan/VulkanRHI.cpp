#include "VulkanRHI.h"

#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanDebugCallback.h"
#include "Vulkan/VulkanPhysicalDevice.h"
#include "Vulkan/VulkanDevice.h"

VulkanRHI::VulkanRHI()
{
    Instance = new VulkanInstance();
    DebugCallback = new VulkanDebugCallback(Instance);
    PhysicalDevice = new VulkanPhysicalDevice(Instance);
    Device = new VulkanDevice(PhysicalDevice);
}

VulkanRHI::~VulkanRHI()
{
    delete Device;
    delete PhysicalDevice;
    delete DebugCallback;
    delete Instance;
}

void VulkanRHI::Initalize()
{
    Instance->Initalize();
    DebugCallback->Initalize();
    PhysicalDevice->PickPhysicalDevice();
    Device->Initalize();
}

void VulkanRHI::Cleanup()
{

    Device->Cleanup();
    DebugCallback->Cleanup();
    Instance->Cleanup();
}