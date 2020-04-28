
#include <unordered_map>

#include "Render.h"
#include "RenderRHI.h"
#include "Shader.h"
#include "RenderMesh.h"
#include "Log.h"

double previousTime = glfwGetTime();
int frameCount = 0;

int main()
{
    
    Render renderer(E_RHITypes::VulkanRHI);

    Shader* vertShader = renderer.RHI->CreateShader();
    vertShader->spirvByteCode = RenderRHI::LoadShader(std::string("/home/steak/Documents/Upsilon/Shaders/vert.spv"));

    Shader* fragShader = renderer.RHI->CreateShader();
    fragShader->spirvByteCode = RenderRHI::LoadShader(std::string("/home/steak/Documents/Upsilon/Shaders/frag.spv"));

    renderer.RHI->shaders.push_back(std::make_pair(vertShader, fragShader));


    RenderMesh* basicMesh = renderer.RHI->CreateMesh();
    basicMesh->rhi = renderer.RHI;

    std::vector<Vertex> verts;
    verts.resize(4);
    verts[0] = Vertex({-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f});
    verts[1] = Vertex({0.5f, -0.5f}, {0.0f, 1.0f, 0.0f});
    verts[2] = Vertex({0.5f, 0.5f}, {0.0f, 0.0f, 1.0f});
    verts[3] = Vertex({-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f});
    basicMesh->Vertices = verts;
    basicMesh->Indices = std::vector<unsigned int> {
        0, 1, 2, 2, 3, 0
    };

    renderer.RHI->meshs.push_back(basicMesh);

    renderer.Initalize();

    while(!glfwWindowShouldClose(renderer.window))
    {
        // Measure speed
        double currentTime = glfwGetTime();
        frameCount++;
        // If a second has passed.
        if ( currentTime - previousTime >= 1.0 )
        {
            // Display the frame count here any way you want.
           
            ULog("Frame Time", std::to_string(((currentTime - previousTime) / frameCount) * 1000));

            frameCount = 0;
            previousTime = currentTime;
        }

        glfwPollEvents();
        renderer.RHI->DrawFrame();


    }

    renderer.Cleanup();

}