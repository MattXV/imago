#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <SDL_image.h>
#include "externals/stb_image/stb_image.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
#include "Utils.h"
#include "RenderUtils.h"


// TODO: Create default texture.

class Texture
{
public:
	Texture(std::string file);
	Texture(const int textureHeight, const int textureWidth, Colour<unsigned char> colour);
	virtual ~Texture() = default;

	unsigned int getTextureId() { return textureId; }
private:

	void setTextureData();

	// Image properties
	std::string file;
	void* textureData = nullptr; // Pointer to raw image data;
	int width = -1, height = -1, channels = -1;
	int imageFormat = -1;

	// GL texture properties
	int glImageFormat = -1;
	unsigned int textureId = 0;

};

