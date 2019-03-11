#ifndef INTERLEAVEDVERTEX__H_
#define INTERLEAVEDVERTEX__H_

#include <glm\glm.hpp>

struct Colour
{
public:
	Colour();
	Colour(float r, float g, float b);
	float r, g, b;

	static Colour White();
	static Colour Red();
	static Colour Black();
	static Colour Blue();
	static Colour Yellow();
	static Colour Green();
};

struct Vertex
{
public:
	glm::vec3 pos;
	Colour colour;
	float u, v;
};

#endif
