#include "DynamicMesh.h"
#include <glad\glad.h>


DynamicMesh::DynamicMesh()
{
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

void DynamicMesh::reinitialiseMesh()
{
	initialiseMeshBuffer();
}

void DynamicMesh::updateMesh()
{
	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, VertexCount() * sizeof(Vertex), Vertices());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, IndexCount() * sizeof(int), Indices());

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, VertexCount() * sizeof(Vertex), 0, GL_DYNAMIC_DRAW);
	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount() * sizeof(int), 0, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
