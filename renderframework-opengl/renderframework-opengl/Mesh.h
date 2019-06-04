#ifndef MESH__H_
#define MESH__H_

#include "InterleavedVertex.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual void setVertices(const Vertex * vertices, int vertexCount);
	virtual void setIndices(const int * indices, int indexCount);
	void useTriangleList();
	void useTriangleStrip();

	int IndexCount();
	int VertexCount();
	int TriangleCount();
	int MeshType();

	const Vertex* const Vertices();
	const int* const Indices();

protected:
	std::vector<int> indices;
	std::vector<Vertex> vertices;

	int triangleCount, meshType;
};

#endif