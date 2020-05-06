#include "Vulkan/VulkanPhysicalDevice.h"

#include "Vulkan/VulkanInstance.h"
#include "Log.h"

VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance* instance)
{
    Instance = instance;
}

void VulkanPhysicalDevice::PickPhysicalDevice()
{

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(Instance->instance, &deviceCount, nullptr);

    if(deviceCount == 0)
    {
        ULogError("Vulkan Physical Device", "Could not find any GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(Instance->instance, &deviceCount, devices.data());

    for(const auto& device : devices)
    {
        if(IsDeviceSuitable(device))
        {
            physicalDevice = device;
            break;
        }
    }

    if(physicalDevice == VK_NULL_HANDLE)
    {
        ULogError("Vulkan Physical Device", "Could not find a suitable GPU!");
    }

}

QueueFamilyIndices VulkanPhysicalDevice::GetQueueFamilies()
{
    return FindQueueFamilies(physicalDevice);
}

QueueFamilyIndices VulkanPhysicalDevice::FindQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device,  &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for(const auto& queueFamily : queueFamilies)
    {
        if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicsFamily = i;
        }

        if(indices.isComplete())
        {
            break;
        }
    }

    return indices;
}

bool VulkanPhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
    QueueFamilyIndices indices = FindQueueFamilies(device);

    return indices.isComplete();
}

bool QueueFamilyIndices::isComplete()
{
    return graphicsFamily.has_value();
}
