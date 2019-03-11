#ifndef SQUARE__H_
#define SQUARE__H_

#include "Mesh.h"

class Square
{
public:
	Square();
	~Square();

	void draw();

private:
	void setupMesh();
	void setupVAO();

	unsigned int vertexArrayID, vertexBufferID, elementBufferID;
	Mesh mesh;
};

#endif