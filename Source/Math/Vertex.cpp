#include "Vertex.h"

Vertex2D::Vertex2D()
{

}

Vertex2D::Vertex2D(glm::vec2 Pos, glm::vec3 Col)
{
    Position = Pos;
    Color = Col;
}

Vertex3D::Vertex3D()
{

}

Vertex3D::Vertex3D(glm::vec3 Pos, glm::vec3 Col)
{
    Position = Pos;
    Color = Col;
}