
#ifndef __UPSILON_RENDER_RENDERWINDOW_H__
#define __UPSILON_RENDER_RENDERWINDOW_H__

#include <string>

#include <GLFW/glfw3.h>

class RenderRHI;

class RenderWindow
{

public:
    RenderWindow();

public:
    GLFWwindow* glfwWin;

    RenderRHI* rhi;

public:
    void CreateWindow(const std::string name);
    void CloseWindow();

    void SetWindowName(const std::string name);

    void SetFullscreen(bool fullscreen);

    void GetWindowSize(int& width, int& height);
    void GetFramebufferSize(int& width, int& height);

    void SetWindowSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);
    void GetWindowSizeLimits(int& minWidth, int& minHeight, int& maxWidth, int& maxHeight);

    bool ShouldWindowClose();

    static void PollEvents();


private:
    std::string windowName;
    int minimumWidth, minimumHeight, maximumWidth, maximumHeight;


};

#endif // __UPSILON_RENDER_RENDERWINDOW_H__