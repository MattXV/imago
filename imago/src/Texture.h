#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "externals/stb_image/stb_image.h"
#include <algorithm>
#include "Utils.h"


// TODO: Create default texture.

class Texture
{
public:
	Texture(std::string file);
	Texture();
	virtual ~Texture() = default;

	unsigned int getTextureId() { return textureId; }
private:

	void setTextureData();

	// Image properties
	std::string file;
	void* textureData = nullptr; // Pointer to raw image data;
	int dataType = -1;			 // Details the pointer above.
	int width = -1, height = -1, channels = -1;
	int imageFormat = -1;

	// GL texture properties
	int glImageFormat = -1;
	unsigned int textureId = 0;

};

