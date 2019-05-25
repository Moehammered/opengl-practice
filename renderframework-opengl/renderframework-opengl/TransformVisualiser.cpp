#include "TransformVisualiser.h"
#include "Camera.h"
#include <glad\glad.h>
#include "TransformHelperFunctions.h"

TransformVisualiser::TransformVisualiser()
{
}


TransformVisualiser::~TransformVisualiser()
{
}

void TransformVisualiser::initialise()
{
	printf("Visualiser init start\n\n");
	RenderComponent::initialise(); //call base - for now all thats needed
	if (material)
		delete material;
	material = nullptr;
	material = new Material("VertexColourTransform.vs", "VertexColourTransform.fs");
	lineColours[0] = Colour::Blue();
	lineColours[1] = Colour::Red();
	lineColours[2] = Colour::Green();
	vertBuffer = new Vertex[2];
	int indices[2] = { 0, 1 };
	//uvs same for all lines
	vertBuffer[0].uv = glm::vec2(0, 0);
	vertBuffer[1].uv = glm::vec2(1, 1);
	//forward setup
	vertBuffer[0].pos = glm::vec3(0);
	vertBuffer[1].pos = glm::vec3(0, 0, -2);
	vertBuffer[0].colour = lineColours[0];
	vertBuffer[1].colour = lineColours[0];
	setupLine(forward, vertBuffer);
	//right setup
	vertBuffer[1].pos = glm::vec3(2, 0, 0);
	vertBuffer[0].colour = lineColours[1];
	vertBuffer[1].colour = lineColours[1];
	setupLine(right, vertBuffer);
	//up setup
	vertBuffer[1].pos = glm::vec3(0, 1, 0);
	vertBuffer[0].colour = lineColours[2];
	vertBuffer[1].colour = lineColours[2];
	setupLine(up, vertBuffer);
}

void TransformVisualiser::draw()
{
	if (material)
	{
		if (Camera::MainCamera)
		{
			material->use();
			material->setTransformProperty("transform",
				Camera::MainCamera->ProjView() * owner->transform.TransformMat4());
			drawAxis(forward, right, up);
		}
	}
}

void TransformVisualiser::setupLine(DynamicMesh & mesh, Vertex * const vertBuffer)
{
	int indices[2] = { 0, 1 };

	material->use();
	mesh.setVertices(vertBuffer, 2);
	mesh.setIndices(indices, 2);
	mesh.setMeshType(GL_LINES);

	mesh.bindVAO();
	mesh.bindVertexBuffer();
	glDisableVertexAttribArray(2);
	mesh.unbindAll();
	mesh.updateMesh();
}

void TransformVisualiser::drawAxis(DynamicMesh & forward, DynamicMesh & right, DynamicMesh & up)
{
	GLint premode = 0;
	GLboolean depthmode = 0;
	glGetIntegerv(GL_POLYGON_MODE, &premode);
	glGetBooleanv(GL_DEPTH_TEST, &depthmode);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_DEPTH_TEST);
	glLineWidth(5);
	forward.draw();
	right.draw();
	up.draw();
	glPolygonMode(GL_FRONT_AND_BACK, premode);
	if (depthmode)
		glEnable(GL_DEPTH_TEST);
}