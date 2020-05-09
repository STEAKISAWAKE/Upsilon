#include "Render.h"
#include "RenderRHI.h"
#include "Shader.h"
#include "Vertex.h"
#include "RenderMesh.h"

int main()
{

    Render render(E_VulkanRHI);

    Shader* vert = render.RHI->CreateShader(0, E_VertexShader, RenderRHI::LoadShader("C:\\Users\\Steak\\Documents\\GitHub\\Upsilon\\Shaders\\vert.spv"));
    Shader* frag = render.RHI->CreateShader(0, E_FragmentShader, RenderRHI::LoadShader("C:\\Users\\Steak\\Documents\\GitHub\\Upsilon\\Shaders\\frag.spv"));

    RenderMesh* mesh = render.RHI->CreateMesh();

    const std::vector<Vertex2D> vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
    };

    const std::vector<uint32_t> indices = 
    {
        0, 1, 2, 2, 3, 0
    };

    mesh->Vertices = vertices;
    mesh->Indices = indices;

    render.Initalize();

    while (!render.Window.ShouldWindowClose())
    {
        RenderWindow::PollEvents();
        
        render.RHI->DrawFrame();

    }

    render.Cleanup();
}
