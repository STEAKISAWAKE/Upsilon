#include "Render.h"
#include "RenderRHI.h"
#include "Shader.h"
#include "Vertex.h"
#include "RenderMesh.h"

#include "Vulkan/VulkanRHI.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanMesh.h"
#include "Vulkan/VulkanCameraUniformBuffer.h"

#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main()
{

    Render render(E_VulkanRHI);

    Shader* vert = render.RHI->CreateShader(0, E_VertexShader, RenderRHI::LoadShader("C:\\Users\\Steak\\Documents\\GitHub\\Upsilon\\Shaders\\vert.spv"));
    Shader* frag = render.RHI->CreateShader(0, E_FragmentShader, RenderRHI::LoadShader("C:\\Users\\Steak\\Documents\\GitHub\\Upsilon\\Shaders\\frag.spv"));

    RenderMesh* mesh = render.RHI->CreateMesh();
    RenderMesh* mesh2 = render.RHI->CreateMesh();

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

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)static_cast<VulkanRHI*>(render.RHI)->SwapChain->swapChainExtent.width / (float)static_cast<VulkanRHI*>(render.RHI)->SwapChain->swapChainExtent.height, 0.1f, 10.0f);


    static_cast<VulkanMesh*>(mesh)->CUB.model = model;
    static_cast<VulkanMesh*>(mesh)->CUB.view = view;
    static_cast<VulkanMesh*>(mesh)->CUB.projection = proj;


    glm::mat4 model2 = glm::translate(glm::rotate(glm::mat4(1.0f), glm::radians(65.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(-4.0f, 0.0f, 0.0f));

    static_cast<VulkanMesh*>(mesh2)->CUB.model = model2;
    static_cast<VulkanMesh*>(mesh2)->CUB.view = view;
    static_cast<VulkanMesh*>(mesh2)->CUB.projection = proj;

    static_cast<VulkanMesh*>(mesh)->CUB.projection[1][1] *= -1;
    static_cast<VulkanMesh*>(mesh2)->CUB.projection[1][1] *= -1;


    mesh->Vertices = vertices;
    mesh->Indices = indices;

    mesh2->Vertices = vertices;
    mesh2->Indices = indices;

    render.Initalize();

    while (!render.Window.ShouldWindowClose())
    {
        RenderWindow::PollEvents();
        
        render.RHI->DrawFrame();

    }

    render.Cleanup();
}
