#include "Line.h"
#include <glad\glad.h>
#include <iostream>
#include <string>

Line::Line()
{
	start = glm::vec3(0, 0, 0);
	end = glm::vec3(0, 0, -1);
	colour = Colour::Red();
	buildLineVertices();
}

Line::Line(glm::vec3 start, glm::vec3 end, Colour colour)
{
	this->start = start;
	this->end = end;
	this->colour = colour;
	buildLineVertices();
}

void Line::draw()
{
	GLint premode = 0;
	GLboolean depthmode = 0;
	glGetIntegerv(GL_POLYGON_MODE, &premode);
	glGetBooleanv(GL_DEPTH_TEST, &depthmode);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_DEPTH_TEST);
	glLineWidth(5);
	glBindVertexArray(vertexArrayID);
	glDrawElements(meshType, 2, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, premode);
	if(depthmode)
		glEnable(GL_DEPTH_TEST);
}

Line::~Line()
{}

void Line::buildLineVertices()
{
	Vertex verts[2];
	verts[0].pos = start;
	verts[0].uv = glm::vec2(0, 0);
	verts[0].colour = colour;

	verts[1].pos = end;
	verts[1].uv = glm::vec2(1, 1);
	verts[1].colour = colour;

	int indices[2] = 
	{
		0, 1
	};

	meshType = GL_LINES;
	setVertices(verts, 2);
	setIndices(indices, 2);
	updateMesh();
}
