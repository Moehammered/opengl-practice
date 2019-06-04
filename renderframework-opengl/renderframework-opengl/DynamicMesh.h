#pragma once
#include "StaticMesh.h"
class DynamicMesh :
	public StaticMesh
{
public:
	DynamicMesh();
	~DynamicMesh();

	void bindVAO();
	void bindVertexBuffer();
	void bindElementBuffer();
	void unbindAll();
	void updateMesh() override;
	void setVertices(const Vertex* vertices, int vertexCount) override;
	void setIndices(const int* indices, int indexCount) override;
	void setMeshType(int type);

protected:
	unsigned int bufferUpdateFlag;
	const unsigned int VERT_BUFFER_SIZE_BIT = 0x1;
	const unsigned int VERT_BUFFER_DATA_BIT = 0x2;
	const unsigned int ELEM_BUFFER_SIZE_BIT = 0x4;
	const unsigned int ELEM_BUFFER_DATA_BIT = 0x8;
	unsigned int VERT_ELEM_DATA_BITS;
	unsigned int VERT_ELEM_SIZE_BITS;
	void initialiseVAO() override;

	void initialiseMeshBuffer();
};

