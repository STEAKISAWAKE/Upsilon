# Create Executable
add_executable(VulkanTests
    main.cpp
)

# Add Library Includes
# target_include_directories(UpsilonRender PUBLIC "${INCLUDE_DIR}/Base")
# target_include_directories(UpsilonRender PUBLIC "${INCLUDE_DIR}/Math")
target_include_directories(VulkanTests PUBLIC "${INCLUDE_DIR}/Render")

# Link Library to Executable
target_link_libraries(VulkanTests UpsilonRender)