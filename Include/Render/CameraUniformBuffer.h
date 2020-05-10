#ifndef __UPSILON_RENDER_CAMERAUNIFORMBUFFER_H__
#define __UPSILON_RENDER_CAMERAUNIFORMBUFFER_H__

#include <glm/mat4x4.hpp>

class CameraUniformBuffer
{

public:
    CameraUniformBuffer();

public:
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

};

#endif // __UPSILON_RENDER_CAMERAUNIFORMBUFFER_H__
