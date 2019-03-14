#include "Texture.h"
#include "stb_image.h"
#include <glad\glad.h>
#include "HelperFunctions.h"

Texture::Texture(std::string path)
{
	maxActiveTextures = GL_TEXTURE31 - GL_TEXTURE0;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channelCount, 0);

	if (data)
	{
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		use();
		//configure
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//upload texture data
		GLuint imageFormat = channelCount == 4 ? GL_RGBA : GL_RGB;		
		glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 
			0, imageFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0); //unbind, finished config

		stbi_image_free(data);
	}
	else
	{
		printLine("Error loading texture: " + path);
	}
}


Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

const int Texture::Width()
{
	return width;
}

const int Texture::Height()
{
	return height;
}

const int Texture::ChannelCount()
{
	return channelCount;
}

const unsigned int Texture::ID()
{
	return textureID;
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::use(unsigned char textureNumber)
{
	textureNumber = textureNumber > maxActiveTextures ? 
		maxActiveTextures : textureNumber;

	glActiveTexture(GL_TEXTURE0 + textureNumber);
	use();
}
