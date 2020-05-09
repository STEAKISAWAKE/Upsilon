#include "RenderMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "RenderRHI.h"

RenderMesh::RenderMesh(RenderRHI* rhi)
{
	RHI = rhi;
	RHI->Meshes.push_back(this);
}

void RenderMesh::Draw(int info)
{

}

void RenderMesh::Initalize()
{

}

void RenderMesh::Cleanup()
{
	
}

bool RenderMesh::LoadMesh(std::string path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)


	// Fill vertices positions
	Vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];

		aiVector3D n;
		if(mesh->mNormals)
			 n = mesh->mNormals[i];

		// Create verts
		//Vertices.push_back(Vertex3D(glm::vec3(pos.x, pos.y, pos.z), { 0.5f, 0.5f, 0.5f } /*, { n.x, n.y, n.z } */));
	}

	//// Fill vertices texture coordinates
	//uvs.reserve(mesh->mNumVertices);
	//for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
	//	aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
	//	uvs.push_back(glm::vec2(UVW.x, UVW.y));
	//}




	// Fill face indices
	Indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		// Assume the model has only triangles.
		Indices.push_back(mesh->mFaces[i].mIndices[0]);
		Indices.push_back(mesh->mFaces[i].mIndices[1]);
		Indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	// The "scene" pointer will be deleted automatically by "importer"
	return true;
}
