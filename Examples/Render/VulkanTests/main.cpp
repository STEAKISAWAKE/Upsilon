
#include <unordered_map>
#include <chrono>
#include <filesystem>

#include "Render.h"
#include "RenderRHI.h"
#include "Shader.h"
#include "RenderMesh.h"
#include "Log.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/mat4x4.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#ifdef _WIN32
    #include <windows.h>    //GetModuleFileNameW
#else
    #include <limits.h>
    #include <unistd.h>     //readlink
#endif


std::filesystem::path getexepath()
{
#ifdef _WIN32
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return path;
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
#endif
}

double previousTime = glfwGetTime();
double previousTimeCube = glfwGetTime();
int frameCount = 0;


Render renderer(E_RHITypes::VulkanRHI);

RenderMesh* basicMesh;
RenderMesh* basicMesh2;

float lastX = 400, lastY = 300;


// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraSpeed = 10.f;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

int main()
{

    std::string exePath = getexepath().string();
    size_t found = exePath.find_last_of("\\");
    exePath.resize(found);

    std::string vertexPath = exePath + std::string("\\Shaders\\vert.spv");

    // Create Shaders
    Shader* vertShader = renderer.RHI->CreateShader(renderer.RHI->GetLatestShaderIndex(), ShaderType::E_VertexShader);
    vertShader->spirvByteCode = RenderRHI::LoadShader(vertexPath);

    Shader* fragShader = renderer.RHI->CreateShader(renderer.RHI->GetLatestShaderIndex(), ShaderType::E_FragmentShader);
    fragShader->spirvByteCode = RenderRHI::LoadShader(exePath + std::string("\\Shaders\\frag.spv"));

    // Create Mesh
    basicMesh = renderer.RHI->CreateMesh();
    basicMesh2 = renderer.RHI->CreateMesh();

    basicMesh->uniformBuffer.model = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f)), 1.0f, glm::vec3(1.3f, 0, 0));

    basicMesh2->uniformBuffer.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    static const Vertex g_vertex_buffer_data[] = {
        Vertex({ -1.0, -1.0,  1.0 },  { 1.0, 0.0, 0.0 }),  // -X side
        Vertex({ 1.0, -1.0,  1.0 },   { 0.0, 1.0, 0.0 }),
        Vertex({ 1.0,  1.0,  1.0 },   { 0.0, 0.0, 1.0 }),
        Vertex({ -1.0,  1.0,  1.0 },  { 1.0, 1.0, 1.0 }),
        Vertex({ -1.0, -1.0, -1.0 },  { 1.0, 0.0, 0.0 }),
        Vertex({ 1.0, -1.0, -1.0 },   { 0.0, 1.0, 0.0 }),
        Vertex({ 1.0,  1.0, -1.0 },   { 0.0, 0.0, 1.0 }),  // -Z side
        Vertex({ -1.0,  1.0, -1.0 },  { 1.0, 1.0, 1.0 })
    };

    std::vector<unsigned int> indices {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

    // Define Mesh
    std::vector<Vertex> verts(g_vertex_buffer_data, g_vertex_buffer_data + sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]));

    basicMesh->Vertices = verts;
    basicMesh->Indices = indices;

    basicMesh2->Vertices = verts;
    basicMesh2->Indices = indices;

    // Initalize renderer
    renderer.Initalize();

    glfwSetCursorPosCallback(renderer.window, mouse_callback);

    glfwSetInputMode(renderer.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    while(!glfwWindowShouldClose(renderer.window))
    {

        // Measure speed
        double currentTime = glfwGetTime();

        float deltaTime = (currentTime - previousTimeCube);

        float speed = 5;

        basicMesh2->uniformBuffer.model = glm::rotate(basicMesh2->uniformBuffer.model, deltaTime * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        basicMesh2->uniformBuffer.model = glm::rotate(basicMesh2->uniformBuffer.model, deltaTime * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        basicMesh2->uniformBuffer.model = glm::rotate(basicMesh2->uniformBuffer.model, deltaTime * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));


// Set Camera Position

        if (glfwGetKey(renderer.window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += (cameraSpeed * cameraFront) * deltaTime;

        if (glfwGetKey(renderer.window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= (cameraSpeed * cameraFront) * deltaTime;

        if (glfwGetKey(renderer.window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= (glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed) * deltaTime;

        if (glfwGetKey(renderer.window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += (glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed) * deltaTime;

// Set Camera Rotation


        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw));
        direction.z = sin(glm::radians(yaw));
        direction.y = sin(glm::radians(pitch));

        //renderer.camera = glm::mat4(1.0f);

        renderer.camera = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


        glfwPollEvents();
        renderer.RHI->DrawFrame();


        frameCount++;
        // If a second has passed.
        if (currentTime - previousTime >= 1.0)
        {
            // Display the frame count here any way you want.

            ULog("Frame Time", std::to_string(((currentTime - previousTime) / frameCount) * 1000));

            frameCount = 0;
            previousTime = currentTime;
        }

        previousTimeCube = currentTime;


    }

    renderer.Cleanup();

}