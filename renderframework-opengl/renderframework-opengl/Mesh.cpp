#include "Mesh.h"

#include <GLFW\glfw3.h>

Mesh::Mesh()
{
	triangleCount = 0;
	meshType = GL_TRIANGLES;
}

Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
}

void Mesh::setVertices(Vertex * vertices, int vertexCount)
{
	this->vertices.clear();
	this->vertices.reserve(vertexCount);
	this->vertices.insert(this->vertices.begin(), vertices, vertices + vertexCount);
}

void Mesh::setIndices(int * indices, int indexCount)
{
	this->indices.clear();
	this->indices.reserve(indexCount);
	this->indices.insert(this->indices.begin(), indices, indices + indexCount);

	triangleCount = meshType == GL_TRIANGLES ? indexCount / 3 : indexCount - 2;
}

void Mesh::useTriangleList()
{
	meshType = GL_TRIANGLES;
	triangleCount = indices.size() / 3;
}

void Mesh::useTriangleStrip()
{
	meshType = GL_TRIANGLE_STRIP;
	triangleCount = indices.size() - 2;
}

int Mesh::IndexCount()
{
	return indices.size();
}

int Mesh::VertexCount()
{
	return vertices.size();
}

int Mesh::TriangleCount()
{
	return triangleCount;
}

int Mesh::MeshType()
{
	return meshType;
}

Vertex * const Mesh::Vertices()
{
	return vertices.data();
}

int * const Mesh::Indices()
{
	return indices.data();
}
