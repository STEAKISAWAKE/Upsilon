
#ifndef __UPSILON_MATH_VERTEX_H__
#define __UPSILON_MATH_VERTEX_H__

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Vertex2D
{

public:
    Vertex2D();
    Vertex2D(glm::vec2 Pos, glm::vec3 Col);

public:
    glm::vec2 Position;
    glm::vec3 Color;

};

class Vertex3D
{

public:
    Vertex3D();
    Vertex3D(glm::vec3 Pos, glm::vec3 Col);

public:
    glm::vec3 Position;
    glm::vec3 Color;

};

#endif // __UPSILON_MATH_VERTEX_H__
