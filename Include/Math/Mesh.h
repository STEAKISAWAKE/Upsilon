
#ifndef __UPSILON_MATH_MESH_H__
#define __UPSILON_MATH_MESH_H__

#include <vector>

#include "Vertex.h"

struct Mesh
{
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
};

#endif // __UPSILON_MATH_MESH_H__
