#include "StaticMesh.h"
#include <glad\glad.h>
#include <iostream>

StaticMesh::StaticMesh()
{
	std::cout << "SM constructor activated" << std::endl;
	vertexArrayID = vertexBufferID = elementBufferID = 0;
	initialiseVAO();
}

StaticMesh::~StaticMesh()
{
	glDeleteVertexArrays(1, &vertexArrayID);
	vertexArrayID = 0;
	glDeleteBuffers(1, &vertexBufferID);
	vertexBufferID = 0;
	glDeleteBuffers(1, &elementBufferID);
	elementBufferID = 0;
}

void StaticMesh::updateMesh()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, VertexCount() * sizeof(Vertex), Vertices(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount() * sizeof(int), Indices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void StaticMesh::draw()
{
	glBindVertexArray(vertexArrayID);
	glDrawElements(MeshType(), IndexCount(), GL_UNSIGNED_INT, 0);
}

void StaticMesh::initialiseVAO()
{
	//create vert and element buffers
	glGenBuffers(1, &vertexBufferID);
	glGenBuffers(1, &elementBufferID);
	//create the VAO buffer
	glGenVertexArrays(1, &vertexArrayID);
	//setup the vertex buffer attributes
	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, Vertex::colour)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, Vertex::uv)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBindVertexArray(0);
}
