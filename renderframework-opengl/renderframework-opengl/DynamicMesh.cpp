#include "DynamicMesh.h"
#include <glad\glad.h>


DynamicMesh::DynamicMesh()
{
	VERT_ELEM_SIZE_BITS = VERT_BUFFER_SIZE_BIT | ELEM_BUFFER_SIZE_BIT;
	VERT_ELEM_DATA_BITS = VERT_BUFFER_DATA_BIT | ELEM_BUFFER_DATA_BIT;
}


DynamicMesh::~DynamicMesh()
{
}

void DynamicMesh::bindVAO()
{
	glBindVertexArray(vertexArrayID);
}

void DynamicMesh::bindVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
}

void DynamicMesh::bindElementBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
}

void DynamicMesh::unbindAll()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DynamicMesh::updateMesh()
{
	if (bufferUpdateFlag & VERT_ELEM_SIZE_BITS)
		initialiseMeshBuffer();
	if (bufferUpdateFlag & VERT_BUFFER_DATA_BIT)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, VertexCount() * sizeof(Vertex), Vertices());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (bufferUpdateFlag & ELEM_BUFFER_DATA_BIT)
	{
		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, IndexCount() * sizeof(int), Indices());
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	bufferUpdateFlag = 0x0; //clear it as it's finished any updates
}

void DynamicMesh::setVertices(const Vertex * vertices, int vertexCount)
{
	if (vertexCount != VertexCount())
		bufferUpdateFlag = bufferUpdateFlag | VERT_BUFFER_SIZE_BIT;
	bufferUpdateFlag = bufferUpdateFlag | VERT_BUFFER_DATA_BIT;
	StaticMesh::setVertices(vertices, vertexCount);
}

void DynamicMesh::setIndices(const int * indices, int indexCount)
{
	if (indexCount != IndexCount())
		bufferUpdateFlag = bufferUpdateFlag | ELEM_BUFFER_SIZE_BIT;
	bufferUpdateFlag = bufferUpdateFlag | ELEM_BUFFER_DATA_BIT;
	StaticMesh::setIndices(indices, indexCount);
}

void DynamicMesh::setMeshType(int type)
{
	meshType = type;
	if (type == GL_LINES)
		triangleCount = 2;
}

void DynamicMesh::initialiseVAO()
{
	StaticMesh::initialiseVAO(); //call super function for now
	initialiseMeshBuffer();
	updateMesh();
}

void DynamicMesh::initialiseMeshBuffer()
{
	if (bufferUpdateFlag & VERT_BUFFER_SIZE_BIT)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, VertexCount() * sizeof(Vertex), 0, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (bufferUpdateFlag & ELEM_BUFFER_SIZE_BIT)
	{
		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount() * sizeof(int), 0, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}
