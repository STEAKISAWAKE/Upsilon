#ifndef __UPSILON_RENDER_VULKANRENDERRHI_H__
#define __UPSILON_RENDER_VULKANRENDERRHI_H__

#include "RenderRHI.h"

#include <optional>

#include <rttr/registration>

#include <vulkan/vulkan.h>


#include "RenderUniformBuffer.h"
#include "VulkanMesh.h"
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
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
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
    
    // Initalizers
    void Initalize() override;
    void InitalizeShaders() override;
    void InitalizeMeshes() override;
    void InitalizeMeshUniformBuffers() override;

    // Cleanup
    void Cleanup() override;
    void CleanupShaders() override;
    void CleanupMeshes() override;
    void CleanupMeshUniformBuffers() override;
        

    void DrawFrame() override;
    void UpdateUniformBuffers(uint32_t currentImage) override;

    virtual Shader*     CreateShader(int shaderIndex, ShaderType type) override;
    virtual RenderMesh* CreateMesh() override;
    virtual Texture*    CreateTexture() override;



    // Helper Functions
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void CreateVertexBuffer(VulkanMesh* mesh);
    void CreateIndexBuffer(VulkanMesh* mesh);
    void CreateUniformBuffers(VulkanMesh* mesh);

    void CleanupUniformBuffers(VulkanMesh* mesh);
    void CreateDescriptorSets(VulkanMesh* mesh);

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

    void CreateGraphicsPipeline(GraphicsShaders shaders);

    void BeginSingleTimeCommands();
    void EndSingleTimeCommands();

    // Vulkan Functions
    void CreateInstance();
    void SetupDebugMessenger();
    void CreateSurface();
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateAllocator();
    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();
    void CreateDescriptorSetLayout();
    void CreateGraphicsPipelines();
    void CreateTemporaryCommandBuffer();
    void CreateFrameBuffers();
    void CreateCommandPool();
    void CreateDescriptorPool();

    void CreateCommandBuffers();
    void CreateSyncObjects();
    void CleanupSwapChain();
    void RecreateSwapChain();

};




#endif // __UPSILON_RENDER_VULKANRENDERRHI_H__