#ifndef UIRENDERCOMPONENT__H_
#define UIRENDERCOMPONENT__H_

#include "Component.h"
#include "Material.h"
#include "CharacterFontData.h"
#include "InterleavedVertex.h"
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

class UIRenderComponent :
	public Component
{
public:
	UIRenderComponent();
	~UIRenderComponent();

	std::string text;
	glm::vec2 pos;
	float scale;
	bool enabled;
	Material* material;

	void setColour(Colour col);
	void setColour(float r, float g, float b);
	void initialise() override;
	bool isActive() override;
	void draw();

private:
	unsigned int VAO, VBO;
	unsigned int colourUniformLoc, projectionUniformLoc;
	glm::ivec2 canvasSize;
	glm::vec4 renderPlaneVerts[6];
	std::map<char, Character> loadedCharacters;
	Colour colour;

	void loadFont(std::string font);
	void cacheCharacters(FT_Face& face);
	void renderText(glm::vec2 pos);
};

#endif