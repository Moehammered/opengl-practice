#include "UIRenderComponent.h"
#include "RenderQueue.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glad\glad.h>

#define USE_VEC4_RENDERPLANE 1

UIRenderComponent::UIRenderComponent()
{
}

UIRenderComponent::~UIRenderComponent()
{
	delete material;
	material = nullptr;
	printf("UIRenderComponent destructor called\n");
	RenderQueue::Instance()->removeFromQueue(this);
}

void UIRenderComponent::setColour(Colour col)
{
	colour = col;
	//update the colour property in shader
	material->use();
	
}

void UIRenderComponent::setColour(float r, float g, float b)
{
	colour.r = r;
	colour.g = g;
	colour.b = b;
	//update the colour property in shader
}

void UIRenderComponent::initialise()
{
	RenderQueue::Instance()->AddToQueue(this);
	enabled = true;
	material = new Material("font-shader.vs", "font-shader.fs");
	colourUniformLoc = glGetUniformLocation(material->shaderID(), "textColor");
	projectionUniformLoc = glGetUniformLocation(material->shaderID(), "projection");

	renderPlaneVerts[0] = glm::vec4(0, 1, 0, 1); //vec2 pos, vec2 uv 
	renderPlaneVerts[1] = glm::vec4(1, 0, 1, 0); //vec2 pos, vec2 uv 
	renderPlaneVerts[2] = glm::vec4(0, 0, 0, 0); //vec2 pos, vec2 uv 
	renderPlaneVerts[3] = glm::vec4(1, 1, 0, 1); //vec2 pos, vec2 uv 
	renderPlaneVerts[4] = glm::vec4(1, 1, 1, 1); //vec2 pos, vec2 uv 
	renderPlaneVerts[5] = glm::vec4(1, 1, 1, 0); //vec2 pos, vec2 uv 

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
#if USE_VEC4_RENDERPLANE
	glBufferData(GL_ARRAY_BUFFER, sizeof(renderPlaneVerts), NULL, GL_DYNAMIC_DRAW);
#else
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
#endif
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//setup canvas
	canvasSize = glm::ivec2(800, 600);
	material->use();
	glm::mat4 projection = glm::ortho(0.0f, (float)canvasSize.x, (float)canvasSize.y, 0.0f);
	glUniformMatrix4fv(projectionUniformLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//setup colour
	colour = Colour::White();
	glUniform3f(colourUniformLoc, colour.r, colour.g, colour.b);

	scale = 1;
	pos = glm::vec2(40, 40);

	loadFont("arial.ttf");
}

bool UIRenderComponent::isActive()
{
	return enabled & owner->IsActive();
}

void UIRenderComponent::draw()
{
	if (material)
	{
		if (!text.empty())
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			material->use();
			renderText(pos);
		}
	}
}

void UIRenderComponent::loadFont(std::string font)
{
	loadedCharacters.clear();

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		printf("ERROR LOADING FREETYPE\n");
	else
	{
		FT_Face face;
		if (FT_New_Face(ft, font.c_str(), 0, &face))
			printf("ERROR LOADING FONT [%s]\n", font.c_str());
		else
		{
			FT_Set_Pixel_Sizes(face, 0, 48);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			cacheCharacters(face);

			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}
	}
}

void UIRenderComponent::cacheCharacters(FT_Face & face)
{
	for (unsigned char c = 0; c < 128; ++c)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			printf("Failed to load character. [%c]", c);
			continue;
		}
		
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		material->setIntProperty("text", 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
			face->glyph->bitmap.width, face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character genChar = {
			texture, 

			glm::ivec2(face->glyph->bitmap.width,
			face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left,
				face->glyph->bitmap_top),

			face->glyph->advance.x
		};

		loadedCharacters.insert(std::pair<char, Character>(c, genChar));
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void UIRenderComponent::renderText(glm::vec2 pos)
{
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	//go through all the text
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = loadedCharacters[*c];
		//printLine("Rendering: " + std::to_string(ch.advance));
		GLfloat xpos = pos.x + ch.bearing.x * scale;
		GLfloat ypos = pos.y + (loadedCharacters['H'].bearing.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

#if USE_VEC4_RENDERPLANE
		renderPlaneVerts[0].x = xpos; renderPlaneVerts[0].y = ypos + h;
		renderPlaneVerts[1].x = xpos + w; renderPlaneVerts[1].y = ypos;
		renderPlaneVerts[2].x = xpos; renderPlaneVerts[2].y = ypos;
		renderPlaneVerts[3].x = xpos; renderPlaneVerts[3].y = ypos + h;
		renderPlaneVerts[4].x = xpos + w; renderPlaneVerts[4].y = ypos + h;
		renderPlaneVerts[5].x = xpos + w; renderPlaneVerts[5].y = ypos;
#else
		GLfloat vertices[6][4] = {
			{xpos, ypos + h, 0, 1},
			{xpos + w, ypos, 1, 0},
			{xpos, ypos, 0, 0},

			{xpos, ypos + h, 0, 1},
			{xpos + w, ypos + h, 1, 1},
			{xpos + w, ypos, 1, 0}
		};
#endif

		glBindTexture(GL_TEXTURE_2D, ch.fontTextureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
#if USE_VEC4_RENDERPLANE
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(renderPlaneVerts), renderPlaneVerts);
#else
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
#endif
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(renderPlaneVerts), renderPlaneVerts);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
#if USE_VEC4_RENDERPLANE
		glDrawArrays(GL_TRIANGLES, 0, 6);
#else
		glDrawArrays(GL_TRIANGLES, 0, 6);
#endif
		pos.x += (ch.advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
