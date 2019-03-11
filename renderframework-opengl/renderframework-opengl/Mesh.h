#ifndef MESH__H_
#define MESH__H_

#include "InterleavedVertex.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void setVertices(Vertex* vertices, int vertexCount);
	void setIndices(int* indices, int indexCount);
	void useTriangleList();
	void useTriangleStrip();

	int IndexCount();
	int VertexCount();
	int TriangleCount();
	int MeshType();

	Vertex* const Vertices();
	int* const Indices();

protected:
	std::vector<int> indices;
	std::vector<Vertex> vertices;

	int triangleCount, meshType;
};

#endif