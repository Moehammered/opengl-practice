#include "InterleavedVertex.h"

Colour::Colour()
{
	r = g = b = 1;
}

Colour::Colour(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Colour Colour::White()
{
	return Colour();
}

Colour Colour::Red()
{
	return Colour(1, 0, 0);
}

Colour Colour::Black()
{
	return Colour(0,0,0);
}

Colour Colour::Blue()
{
	return Colour(0,0,1);
}

Colour Colour::Yellow()
{
	return Colour(0.3f, 1, 0);
}

Colour Colour::Green()
{
	return Colour(0, 1, 0);
}
