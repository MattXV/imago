#include "Texture.h"
#include "Texture.h"


Texture::Texture(std::string f)
	: file(f)
{
	stbi_set_flip_vertically_on_load(1);
	textureData = stbi_load(file.c_str(), &width, &height, &channels, 0);
	dataType = GL_UNSIGNED_BYTE;
	if (!textureData) {
		throw std::runtime_error("[ERROR] Could not read image file!");
	}
	if (channels == 3) {
		
		imageFormat = GL_RGB8;
		glImageFormat = GL_RGB;
	}
	else if (channels == 4) {

		imageFormat = GL_RGBA8;
		glImageFormat = GL_RGBA;
	}
	else {
		throw std::runtime_error("[ERROR] Could not read image file!");
	}

	setTextureData();
	// Allocate texture in OpenGL
	stbi_image_free(textureData);
}

Texture::Texture() 
{
	// Construct a white dummy texture.
	const int newHeight = 1024;
	const int newWidth = 1024;
	const int newChannels = 4;
	width = newWidth;
	height = newHeight;
	channels = newChannels;
	imageFormat = GL_RGBA8;
	glImageFormat = GL_RGBA;
	// Create an empty char array
	std::vector<unsigned char>* textureArray = new std::vector<unsigned char>();
	textureArray->assign(newHeight * newWidth * newChannels, (unsigned char)255);
	dataType = GL_UNSIGNED_BYTE;
	textureData = (void*)textureArray->data();
	// Set white pixels to the GL Texture.
	setTextureData();

	delete textureArray;
}

void Texture::setTextureData()
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Set how the texture should upscale
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // downscale.
	
	glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, glImageFormat, dataType, textureData);
	glBindTexture(GL_TEXTURE_2D, 0);
}
