
#ifndef __UPSILON_MATH_VERTEX_H__
#define __UPSILON_MATH_VERTEX_H__

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Vertex
{

// Constructors
public:
    Vertex();
    Vertex(glm::vec3 Pos, glm::vec3 Col, glm::vec3 Norm);

// Variables
public:
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec3 Normal;


// Methods


};

#endif // __UPSILON_MATH_VERTEX_H__
