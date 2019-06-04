#pragma once
#include "RenderComponent.h"
#include "VertexArrayObject.h"

class MeshRendererComponent :
	public RenderComponent
{
public:
	MeshRendererComponent();
	~MeshRendererComponent();

	const Mesh& getMesh();
	void setMesh(const Mesh& newMesh);
	void setVertexData(const Vertex* newVerts, const GLuint vertCount);
	void setIndexData(const int * newIndices, const GLuint indCount);
	void initialise() override;
	void draw() override;

private:
	Mesh mesh;
	VertexArrayObject vao;
};

