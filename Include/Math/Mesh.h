
#ifndef __UPSILON_MATH_MESH_H__
#define __UPSILON_MATH_MESH_H__

#include <vector>

#include "Vertex.h"

class Mesh
{

// Constructors
public:
    Mesh();
    Mesh(std::vector<Vertex> Verts, std::vector<unsigned int> Index);


// Variables
public:
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;


// Methods
public:
    

};

#endif // __UPSILON_MATH_MESH_H__
