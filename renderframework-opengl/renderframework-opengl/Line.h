#ifndef LINE__H_
#define LINE__H_

#include "StaticMesh.h"
#include <glm\glm.hpp>
#include "InterleavedVertex.h"

class Line :
	public StaticMesh
{
public:
	Line();
	Line(glm::vec3 start, glm::vec3 end, Colour colour);
	~Line();

	void draw();

protected:
	void buildLineVertices();

	glm::vec3 start, end;
	Colour colour;
};

#endif