#include "Vertex.h"

// Constructors
Vertex::Vertex()
{

}

Vertex::Vertex(glm::vec3 Pos, glm::vec3 Col, glm::vec3 Norm)
{
    Position = Pos;
    Color = Col;
    Normal = Norm;
}