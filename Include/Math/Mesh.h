
#ifndef __UPSILON_MATH_MESH_H__
#define __UPSILON_MATH_MESH_H__

#include <vector>

#include "Vertex.h"

class Mesh
{

public:
    Mesh();
    Mesh(std::vector<Vertex2D> Verts, std::vector<uint32_t> Index);

public:
    std::vector<Vertex2D> Vertices;
    std::vector<uint32_t> Indices;
};

#endif // __UPSILON_MATH_MESH_H__
