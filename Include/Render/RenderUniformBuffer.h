#ifndef __UPSILON_RENDER_RENDERUNIFORMBUFFER_H__
#define __UPSILON_RENDER_RENDERUNIFORMBUFFER_H__

#include <glm/mat4x4.hpp>

class RenderUniformBuffer
{

// Variables
public:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;

};

#endif //  __UPSILON_RENDER_RENDERUNIFORMBUFFER_H__