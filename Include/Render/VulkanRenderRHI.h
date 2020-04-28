#ifndef __UPSILON_RENDER_VULKANRENDERRHI_H__
#define __UPSILON_RENDER_VULKANRENDERRHI_H__

#include "RenderRHI.h"

#include <optional>

#include <rttr/registration>

#include "vulkan/vulkan.h"

#include "VulkanVertex.h"
#include "Shader.h"

class VulkanShader;

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool IsComplete();
}; 

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanRenderRHI 
    : public RenderRHI
{
    
    RTTR_ENABLE(RenderRHI)

// Constructors
public:
  
    VulkanRenderRHI();

// Variables
public:

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    std::vector<VkPipeline> graphicsPipelines;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphore;
    std::vector<VkSemaphore> renderFinishedSemaphore;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;

    bool framebufferResized = false;

// Methods
public:
    virtual void Initalize();
    virtual void Cleanup();

    virtual void DrawFrame();

    virtual Shader*     CreateShader() override;
    virtual RenderMesh* CreateMesh() override;

    // Helper Functions
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

// Variables
private:


// Methods
private:
    // Helper Functions
    bool CheckValidationLayerSupport();

    std::vector<const char*> GetRequiredExtensions(); 

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

    VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, 
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator, 
    VkDebugUtilsMessengerEXT* pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(
         VkInstance instance, 
         VkDebugUtilsMessengerEXT debugMessenger, 
         const VkAllocationCallbacks* pAllocator);

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    
    bool IsDeviceSuitable(VkPhysicalDevice device);

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    void CreateGraphicsPipeline(VulkanShader* vert, VulkanShader* frag);

    // Vulkan Functions
    void CreateInstance();
    void SetupDebugMessenger();
    void CreateSurface();
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();
    void CreateGraphicsPipelines();
    void CreateFrameBuffers();
    void CreateCommandPool();
    void CreateCommandBuffers();
    void CreateSyncObjects();
    void CleanupSwapChain();
    void RecreateSwapChain();

};


#endif // __UPSILON_RENDER_VULKANRENDERRHI_H__