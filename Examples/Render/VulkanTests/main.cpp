#include "Render.h"

int main()
{

    Render render(E_VulkanRHI);

    render.Initalize();

    render.Cleanup();

}
