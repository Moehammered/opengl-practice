#include "Square.h"

#include <glad\glad.h>

Square::Square()
{
	vertexArrayID = vertexBufferID = elementBufferID = 0;

	setupMesh();
	setupVAO();
}

Square::~Square()
{
	glDeleteVertexArrays(1, &vertexArrayID);
	vertexArrayID = 0;
	glDeleteBuffers(1, &vertexBufferID);
	vertexBufferID = 0;
	glDeleteBuffers(1, &elementBufferID);
	elementBufferID = 0;
}

void Square::draw()
{
	glBindVertexArray(vertexArrayID);
	//triangle type, amont of indices to use, the index data type, pointer offset/element data
	glDrawElements(mesh.MeshType(), mesh.IndexCount(), GL_UNSIGNED_INT, 0);
}

void Square::setupMesh()
{
	mesh.useTriangleList();
	Vertex vertices[4];
	//setup the positions
	vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0); //TL
	vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0); //BL
	vertices[2].pos = glm::vec3(0.5f, 0.5f, 0); //TR
	vertices[3].pos = glm::vec3(0.5f, -0.5f, 0); //BR
	
	//setup the indices
	int indices[6]{ 
		0, 1, 2,	//1st tri
		2, 1, 3		//2nd tri
	};

	mesh.setVertices(vertices, 4);
	mesh.setIndices(indices, 6);
}

void Square::setupVAO()
{
	//create the vertex buffer
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, mesh.VertexCount() * sizeof(Vertex), mesh.Vertices(), GL_STATIC_DRAW);
	//create the element buffer
	glGenBuffers(1, &elementBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.IndexCount() * sizeof(int), mesh.Indices(), GL_STATIC_DRAW);
	//create the vertex array
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	//setup vertex position attribute and colour
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, Vertex::colour)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
}
