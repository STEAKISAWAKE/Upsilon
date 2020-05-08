#include "RenderWindow.h"

#include "RenderRHI.h"

#include "Log.h"

#define CHECK_WINDOW(err) if(!glfwWin) ULog("Render Window", err);


void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto renderRHI = reinterpret_cast<RenderRHI*>(glfwGetWindowUserPointer(window));
    renderRHI->FramebufferResized();
}

RenderWindow::RenderWindow()
{
    
}

void RenderWindow::CreateWindow(std::string name)
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    //glfwWin = glfwCreateWindow(mode->width, mode->height, name.c_str(), monitor, nullptr);
    glfwWin = glfwCreateWindow(1080, 720, name.c_str(), nullptr, nullptr);

}

void RenderWindow::CloseWindow()
{
    CHECK_WINDOW("Could not close window that is not open!") return;
    glfwDestroyWindow(glfwWin);
}

void RenderWindow::SetWindowName(const std::string name)
{
    CHECK_WINDOW("Could not set window name that is not open!") return;
    glfwSetWindowTitle(glfwWin, name.c_str());
}

void RenderWindow::SetFullscreen(bool fullscreen)
{
    CHECK_WINDOW("Could not set a window fullscreeen that is not open!") return;

    GLFWmonitor* monitor = glfwGetWindowMonitor(glfwWin);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    if(fullscreen)
    {
        glfwSetWindowMonitor(glfwWin, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(glfwWin, nullptr, GLFW_DONT_CARE, GLFW_DONT_CARE, mode->width, mode->height,  0);
    }
}

void RenderWindow::GetWindowSize(int& width, int& height)
{
    glfwGetWindowSize(glfwWin, &width, &height);
}

void RenderWindow::GetFramebufferSize(int& width, int& height)
{
    glfwGetFramebufferSize(glfwWin, &width, &height);
}

void RenderWindow::SetWindowSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight)
{
    minimumWidth = minWidth; minimumHeight = minWidth; maximumWidth = maxWidth; maximumHeight = maxHeight;
    glfwSetWindowSizeLimits(glfwWin, minWidth, minHeight, maxWidth, maxHeight);
}

void RenderWindow::GetWindowSizeLimits(int& minWidth, int& minHeight, int& maxWidth, int& maxHeight)
{
    minWidth = minimumWidth; minHeight = minimumHeight; maxWidth = maximumWidth; maxHeight = maximumHeight;
}

bool RenderWindow::ShouldWindowClose()
{
    CHECK_WINDOW("Could not check if window should close when not created!")
    return glfwWindowShouldClose(glfwWin);
}

void RenderWindow::PollEvents()
{
    glfwPollEvents();
}