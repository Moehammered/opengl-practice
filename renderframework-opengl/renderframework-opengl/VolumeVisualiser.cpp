#include "VolumeVisualiser.h"
#include <glad\glad.h>
#include "TransformHelperFunctions.h"

VolumeVisualiser::VolumeVisualiser()
{
	lineWidth = 3;
}


VolumeVisualiser::~VolumeVisualiser()
{
}

void VolumeVisualiser::initialise()
{
	printf("Volume visualiser init start\n\n");
	RenderComponent::initialise();
	if (material)
		delete material;
	material = nullptr;
	material = new Material("VertexColourTransform.vs", "VertexColourTransform.fs");
	updateRenderVolume();
}

void VolumeVisualiser::updateRenderVolume()
{
	buildLineMesh();
}

void VolumeVisualiser::draw()
{
	GLint premode = 0;
	GLboolean depthmode = 0;
	glGetIntegerv(GL_POLYGON_MODE, &premode);
	glGetBooleanv(GL_DEPTH_TEST, &depthmode);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_DEPTH_TEST);
	glLineWidth(lineWidth);
	RenderComponent::draw();
	glPolygonMode(GL_FRONT_AND_BACK, premode);
	//if (depthmode)
	//	glEnable(GL_DEPTH_TEST);
}

void VolumeVisualiser::buildLineVerts()
{
	//Vertex vertices[8];
	//setup front points
	glm::vec3 fbr, ftr, ftl, fbl;
	fbl = volumeToRender.minPoint;
	fbr = fbl; fbr.x = volumeToRender.maxPoint.x;
	ftl = fbl; ftl.y = volumeToRender.maxPoint.y;
	ftr = ftl; ftr.x = volumeToRender.maxPoint.x;

	printf("FBL:%s\tFBR:%s\n", vec3ToString(fbl).c_str(), vec3ToString(fbr).c_str());
	printf("FTL:%s\tFTR:%s\n", vec3ToString(ftl).c_str(), vec3ToString(ftr).c_str());
	//setup back points
	glm::vec3 bbr, btr, btl, bbl;
	btr = volumeToRender.maxPoint;
	btl = btr; btl.x = volumeToRender.minPoint.x;
	bbr = btr; bbr.y = volumeToRender.minPoint.y;
	bbl = bbr; bbl.x = volumeToRender.minPoint.x;

	printf("BBL:%s\tBBR:%s\n", vec3ToString(bbl).c_str(), vec3ToString(bbr).c_str());
	printf("BTL:%s\tBTR:%s\n", vec3ToString(btl).c_str(), vec3ToString(btr).c_str());

	//front vertices
	vertices[0].pos = fbl;
	vertices[1].pos = fbr;
	vertices[2].pos = ftl;
	vertices[3].pos = ftr;
	//back vertices
	vertices[4].pos = bbl;
	vertices[5].pos = bbr;
	vertices[6].pos = btl;
	vertices[7].pos = btr;

	//setup rest of the components
	for (int i = 0; i < 8; ++i)
	{
		vertices[i].colour = Colour(0.1f, 0.6f, 0.35f);
		vertices[i].uv = glm::vec2(0);
	}

	//return vertices;
}

void VolumeVisualiser::buildLineMesh()
{
	buildLineVerts();
	//24 points to draw the lines
	int indices[] = {
		0, 1, 0, 2, 2, 3, 3, 1, //front face lines
		4, 5, 4, 6, 6, 7, 7, 5, //back face lines
		0, 4, 1, 5, 2, 6, 3, 7 //connecting lines
	};

	volumeMesh.setVertices(vertices, 8);
	volumeMesh.setIndices(indices, 24);
	volumeMesh.setMeshType(GL_LINES);
	volumeMesh.bindVAO();
	volumeMesh.bindVertexBuffer();
	glDisableVertexAttribArray(2);
	volumeMesh.unbindAll();
	volumeMesh.updateMesh();

	this->mesh = volumeMesh;
}
