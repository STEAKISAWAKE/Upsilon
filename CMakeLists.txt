cmake_minimum_required(VERSION 3.10)

project(Upsilon CXX)

# Main options
option(UPSILON_BUILD_GAME "ON to build the game engine of Upsilon" ON)
option(UPSILON_BUILD_RENDER "ON to build the render engine of Upsilon" ON)

# Other options
option(UPSILON_BUILD_RENDER_VULKAN "ON to target vulkan and opengl" ON)

# Build 3rd Party libraries first
add_subdirectory(Libraries)

# Build Upsilon second
add_subdirectory(Source)

# Build examples last
add_subdirectory(Examples)