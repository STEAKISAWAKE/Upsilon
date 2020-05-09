#include "Mesh.h"

// Constructors
Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<Vertex2D> Verts, std::vector<uint32_t> Index)
{   
    Vertices = Verts; Indices = Index;
}
