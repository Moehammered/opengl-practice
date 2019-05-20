#pragma once

#include <glm\vec2.hpp>

struct Character {
	unsigned int	fontTextureID;
	glm::ivec2		size;			//size of glyph
	glm::ivec2		bearing;		//offset from baseline of glyph
	unsigned int	advance;		//offset to next glyph
};