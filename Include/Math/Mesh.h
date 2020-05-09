
#ifndef __UPSILON_MATH_MESH_H__
#define __UPSILON_MATH_MESH_H__

#include <vector>

#include "Vertex.h"

class Mesh
{

public:
    Mesh();
    Mesh(std::vector<Vertex2D> Verts, std::vector<unsigned int> Index);

public:
    std::vector<Vertex2D> Vertices;
    std::vector<unsigned int> Indices;
};

#endif // __UPSILON_MATH_MESH_H__
