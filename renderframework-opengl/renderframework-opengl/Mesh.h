#ifndef MESH__H_
#define MESH__H_

#include "InterleavedVertex.h"
#include <vector>
#include "VertexArrayObject.h"

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual void setVertices(const Vertex * vertices, int vertexCount);
	virtual void setIndices(const int * indices, int indexCount);
	void useTriangleList();
	void useTriangleStrip();
	void forceBufferPropertyUpdate();

	int IndexCount();
	int VertexCount();
	int TriangleCount();
	int MeshType();
	const std::vector<BufferProperty> VertexBufferProperty() const;

	const Vertex* const Vertices();
	const int* const Indices();

protected:
	std::vector<int> indices;
	std::vector<Vertex> vertices;
	std::vector<BufferProperty> buffers;
	int triangleCount, meshType;

	void updateBufferProperties();

	///flags for modification and updating
		///interesting discovery: member const values cause the copy constructor to be implicitly deleted
	unsigned int updateFlag;
	static const unsigned int VERT_BUFFER_SIZE_BIT = 0x1; //unnecessary?
	static const unsigned int VERT_BUFFER_DATA_BIT = 0x2;
	static const unsigned int ELEM_BUFFER_SIZE_BIT = 0x4; //unnecessary?
	static const unsigned int ELEM_BUFFER_DATA_BIT = 0x8;
	//shortcut for checking if either vert or elem modifications are needed
	static const unsigned int VERT_ELEM_DATA_BITS = VERT_BUFFER_DATA_BIT | ELEM_BUFFER_DATA_BIT;
	static const unsigned int VERT_ELEM_SIZE_BITS = VERT_BUFFER_SIZE_BIT | ELEM_BUFFER_SIZE_BIT;
};

#endif