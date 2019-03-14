#ifndef TEXTURE__H_
#define TEXTURE__H_

#include <string>

class Texture
{
public:
	Texture(std::string path);
	~Texture();

	const int Width();
	const int Height();
	const int ChannelCount();
	const unsigned int ID();

	void use();
	void use(unsigned char textureNumber);

private:
	int width, height, channelCount;
	unsigned char maxActiveTextures;
	unsigned int textureID;
};

#endif