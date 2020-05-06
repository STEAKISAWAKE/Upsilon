#ifndef __UPSILON_RENDER_VULKANINSTANCE__
#define __UPSILON_RENDER_VULKANINSTANCE__

#include "vulkan/vulkan.h"

#include <vector>

class VulkanInstance
{

public:
    VulkanInstance();

public:
    VkInstance instance;

#ifdef NDEBUG
    static const bool enableValidationLayers = false;
#else
    static const bool enableValidationLayers = true;
#endif

    static const std::vector<const char*> validationLayers;

    
public:
    void Initalize();
    void Cleanup();

public:
    static bool CheckValidationLayerSupport();
    static std::vector<const char*> GetRequiredExtensions();
};

#endif // __UPSILON_RENDER_VULKANINSTANCE__