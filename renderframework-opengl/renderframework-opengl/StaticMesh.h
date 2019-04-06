#ifndef STATICMESH__H_
#define STATICMESH__H_

#include "Mesh.h"
class StaticMesh :
	public Mesh
{
public:
	StaticMesh();
	~StaticMesh();

	void updateMesh(); //calling this causes the VAO to be updated with vert data
	virtual void draw(); //might move this into the render component, or keep it as an interface function

protected:
	unsigned int vertexArrayID, vertexBufferID, elementBufferID;

	void initialiseVAO();
};

#endif