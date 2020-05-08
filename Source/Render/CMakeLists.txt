
# Create Library
add_library(UpsilonRender STATIC
    glad.c

    RenderWindow.cpp

    RenderRHI.cpp
    Vulkan/VulkanRHI.cpp
    Vulkan/VulkanInstance.cpp
    Vulkan/VulkanDebugCallback.cpp
    Vulkan/VulkanPhysicalDevice.cpp
    Vulkan/VulkanDevice.cpp
    Vulkan/VulkanSurface.cpp
    Vulkan/VulkanSwapChain.cpp
    Vulkan/VulkanImageViews.cpp
    Vulkan/VulkanShader.cpp
    Vulkan/VulkanRenderPass.cpp
    Vulkan/VulkanGraphicsPipeline.cpp
    Vulkan/VulkanFramebuffers.cpp
    Vulkan/VulkanCommandPool.cpp
    Vulkan/VulkanCommandBuffers.cpp
    Vulkan/VulkanSemaphores.cpp

    Shader.cpp
    Texture.cpp
    RenderMesh.cpp

    Render.cpp
)

# Include Directories
target_include_directories(UpsilonRender PUBLIC "${INCLUDE_DIR}/Base")
target_include_directories(UpsilonRender PUBLIC "${INCLUDE_DIR}/Math")
target_include_directories(UpsilonRender PUBLIC "${INCLUDE_DIR}/Render" "${INCLUDE_DIR}/Render/Vulkan")

# Link Libraries
target_link_libraries(UpsilonRender UpsilonBase)
target_link_libraries(UpsilonRender UpsilonMath)

# Get 3rd Party Libraries
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(Vulkan REQUIRED)

# Include 3rd Party Libraries
target_include_directories(UpsilonRender PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(UpsilonRender PUBLIC ${Vulkan_INCLUDE_DIRS})

message(${Vulkan_INCLUDE_DIRS})

# Link 3rd Party Libraries
target_link_libraries(UpsilonRender ${OPENGL_LIBRARIES})
target_link_libraries(UpsilonRender ${Vulkan_LIBRARY})
target_link_libraries(UpsilonRender glfw)
target_link_libraries(UpsilonRender assimp)