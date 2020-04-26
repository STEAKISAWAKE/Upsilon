
#include <unordered_map>

#include "Render.h"
#include "RenderRHI.h"
#include "Shader.h"

int main()
{
    
    Render renderer(E_RHITypes::VulkanRHI);

    Shader vertShader(renderer.RHI, RenderRHI::LoadShader(std::string("/home/steak/Documents/Upsilon/Shaders/vert.spv")));
    Shader fragShader(renderer.RHI, RenderRHI::LoadShader(std::string("/home/steak/Documents/Upsilon/Shaders/frag.spv")));

    renderer.RHI->shaders.push_back(std::make_pair(&vertShader, &fragShader));

    renderer.Initalize();

    while(!glfwWindowShouldClose(renderer.window))
    {
        glfwPollEvents();
        renderer.RHI->DrawFrame();
    }

    renderer.Cleanup();

}