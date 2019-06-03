#ifndef PRIMITIVESHAPES__H_
#define PRIMITIVESHAPES__H_

#include "StaticMesh.h"

namespace PrimitiveShapes
{
	void CreateCube(StaticMesh& mesh);
	void CreateCube(Mesh& mesh);
	void CreateXYPlane(StaticMesh& mesh);
	void CreateXZPlane(StaticMesh& mesh);
	void CreateTriangle(StaticMesh& mesh);
	void CreateSphere(StaticMesh& mesh);
	void CreatePyramid(StaticMesh& mesh);
}
#endif