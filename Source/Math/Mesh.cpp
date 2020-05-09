#include "Mesh.h"

// Constructors
Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<Vertex2D> Verts, std::vector<unsigned int> Index)
{   
    Vertices = Verts; Indices = Index;
}
