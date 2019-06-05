#ifndef PRIMITIVESHAPES__H_
#define PRIMITIVESHAPES__H_

#include "StaticMesh.h"

namespace PrimitiveShapes
{
	void CreateCube(Mesh& mesh);
	void CreateXYPlane(Mesh & mesh);
	void CreateXZPlane(Mesh & mesh);
	void CreateTriangle(Mesh & mesh);
	void CreateSphere(Mesh & mesh);
	void CreatePyramid(Mesh & mesh);

	Mesh CreateCube();
	Mesh CreateXYPlane();
	Mesh CreateXZPlane();
	Mesh CreateTriangle();
	Mesh CreateSphere();
	Mesh CreatePyramid();
}
#endif