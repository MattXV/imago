#include "Texture.h"


Texture::Texture(std::string f)
	: file(f)
{
	stbi_set_flip_vertically_on_load(1);
	textureData = stbi_load(file.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	//SDL_Surface* image = IMG_Load(file.c_str());
	//width = image->w;
	//height = image->h;
	//textureData = image->pixels;

	//SDL_Surface* surface = IMG_Load(file.c_str());
	//width = surface->w;
	//height = surface->h;
	//surface->


	if (!textureData) {
		std::cerr << "[ERROR] Could not read image file! File: " << file.c_str() << std::endl;
		return;
	}

	//imageFormat = GL_RGB8;
	//glImageFormat = GL_RGB;


	setTextureData();
	// Allocate texture in OpenGL
	stbi_image_free(textureData);
}

Texture::Texture(const int textureHeight, const int textureWidth)
{
	// Construct a white dummy texture.
	const unsigned int newHeight = textureHeight;
	const unsigned int newWidth = textureWidth;
	const unsigned int newChannels = 4;
	width = newWidth;
	height = newHeight;
	channels = newChannels;
	imageFormat = GL_RGBA8;
	glImageFormat = GL_RGBA;
	// Create an empty char array
	std::vector<unsigned char>* textureArray = new std::vector<unsigned char>();
	textureArray->assign(((long int)newHeight * (long int)newWidth * (long int)newChannels), (unsigned char)180);
	textureData = (void*)textureArray->data();
	// Set white pixels to the GL Texture.
	setTextureData();

	delete textureArray;
}

void Texture::setTextureData()
{
	GLCALL(glGenTextures(1, &textureId));
	GLCALL(glBindTexture(GL_TEXTURE_2D, textureId));
	
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // Set how the texture should upscale
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));  // and downscale.
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData));

	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}
