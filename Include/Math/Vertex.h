
#ifndef __UPSILON_MATH_VERTEX_H__
#define __UPSILON_MATH_VERTEX_H__

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Vertex
{

// Constructors
public:
    Vertex();
    Vertex(glm::vec2 Pos, glm::vec3 Col);

// Variables
public:
    glm::vec2 Position;
    glm::vec3 Color;


// Methods


};

#endif // __UPSILON_MATH_VERTEX_H__
