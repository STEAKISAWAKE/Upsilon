
# Create Library
add_library(UpsilonRender STATIC
    Render.cpp
    RenderRHI.cpp
    Shader.cpp
    VulkanShader.cpp
    VulkanRenderRHI.cpp
)

# Include Directories
target_include_directories(UpsilonRender PUBLIC "${INCLUDE_DIR}/Base")
target_include_directories(UpsilonRender PUBLIC "${INCLUDE_DIR}/Math")
target_include_directories(UpsilonRender PUBLIC "${INCLUDE_DIR}/Render")

# Link Libraries
target_link_libraries(UpsilonRender UpsilonBase)
target_link_libraries(UpsilonRender UpsilonMath)

# Get 3rd Party Libraries
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(Vulkan REQUIRED)

# Include 3rd Party Libraries
target_include_directories(UpsilonRender PUBLIC OPENGL_INCLUDE_DIR)
target_include_directories(UpsilonRender PUBLIC Vulkan_INCLUDE_DIRS)

# Link 3rd Party Libraries
target_link_libraries(UpsilonRender ${OPENGL_LIBRARIES})
target_link_libraries(UpsilonRender ${Vulkan_LIBRARY})
target_link_libraries(UpsilonRender glfw)
