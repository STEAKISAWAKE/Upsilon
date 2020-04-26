
#include <unordered_map>

#include "Render.h"
#include "RenderRHI.h"
#include "Shader.h"
#include "Log.h"

double previousTime = glfwGetTime();
int frameCount = 0;

int main()
{
    
    Render renderer(E_RHITypes::VulkanRHI);

    Shader vertShader(renderer.RHI, RenderRHI::LoadShader(std::string("/home/steak/Documents/Upsilon/Shaders/vert.spv")));
    Shader fragShader(renderer.RHI, RenderRHI::LoadShader(std::string("/home/steak/Documents/Upsilon/Shaders/frag.spv")));

    renderer.RHI->shaders.push_back(std::make_pair(&vertShader, &fragShader));

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