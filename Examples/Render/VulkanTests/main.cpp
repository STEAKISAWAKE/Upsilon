#include "Render.h"
#include "RenderRHI.h"
#include "Shader.h"

int main()
{

    Render render(E_VulkanRHI);

    Shader* vert = render.RHI->CreateShader(0, E_VertexShader, RenderRHI::LoadShader("C:\\Users\\Steak\\Documents\\GitHub\\Upsilon\\Shaders\\vert.spv"));
    Shader* frag = render.RHI->CreateShader(0, E_FragmentShader, RenderRHI::LoadShader("C:\\Users\\Steak\\Documents\\GitHub\\Upsilon\\Shaders\\frag.spv"));

    render.Initalize();

    while (!render.Window.ShouldWindowClose())
    {
        RenderWindow::PollEvents();
        
        render.RHI->DrawFrame();

    }

    render.Cleanup();
}
