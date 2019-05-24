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
	void reinitialiseMesh();
	void updateMesh() override;
	void setMeshType(int type);

protected:
	void initialiseVAO() override;

	void initialiseMeshBuffer();
};

