#include "Terrain.h"

Terrain::Terrain(const std::string& heightmapFile, Texture* texture)
	: texture(texture)
{
	// Step 1: Load the heightmap file.
	stbi_set_flip_vertically_on_load(1);
	int height = -1, width = -1, channels = -1;
	unsigned char* imageData = stbi_load(heightmapFile.c_str(), &width, &height, &channels, 0);
	if (channels == -1) {
		std::cerr << "Could not read image! Error: " << stbi_failure_reason() << std::endl;
		return;
	}

	// Step 2: Create vertex data from heightmap file.
	std::vector<Vertex> vertices;
	float tileWidth, tileHeight;
	unsigned char red, green, blue;
	int heightValue;
	float x, y, z, u, v;

	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			tileWidth = (float)(width - 1);
			tileHeight = (float)(height - 1);

			red = imageData[(column + row * width) * channels + 0];
			green = imageData[(column + row * width) * channels + 1];
			blue = imageData[(column + row * width) * channels + 2];

			heightValue = ((int)red + (int)green + (int)blue) / 3; // This is the resulting terrain height value

			// The following creates vertex data from the height value sampled from the image.
			x = ((float)column / tileWidth) * tileSize; // the subtraction centres the tile around 0
			y = ((float)heightValue / 255.0f - 1.0f) * tileScaling;
			z = ((float)row / tileHeight) * tileSize;
			u = (float)column / tileWidth;
			v = (float)(tileHeight - row) / tileHeight;

			vertices.emplace_back(x, y, z, u, v);
		}
	}

	// Create index data
	std::vector<unsigned int> indices;
	unsigned int topLeft, topRight, bottomLeft, bottomRight;
	for (int row = 0; row < height - 1; row++) { // Careful, we're indexing tiles here!
		for (int column = 0; column < width - 1; column++) {
			topLeft = (unsigned int)(column + row * width);
			topRight = (unsigned int)(column + row * width + 1);
			bottomLeft = (unsigned int)((row + 1) * width + column);
			bottomRight = (unsigned int)((row + 1) * width + column + 1);
			// It's a square we're indexing. Hence, we need to produce indices for two triangles.

			indices.push_back(topLeft);     // First triangle   *--*--*--------------
			indices.push_back(bottomLeft);	//					| /| /| 
			indices.push_back(topRight);    //                  |/ |/ |  and so on...
											//                  *--*--*--------------
			indices.push_back(topRight);    // Second triangle  | /|  terrain tiles
			indices.push_back(bottomLeft);  //                  |/ |  viewed from 
			indices.push_back(bottomRight); //					*--*  the top
											//					|  |
		}
	}
	indexCount = indices.size();

	// Transfer these vectors containing our mesh data to OpenGL buffers.
	vboLocation = RenderUtils::createVBO(vertices);
	iboLocation = RenderUtils::createIBO(indices);
	// Clean up!
	stbi_image_free(imageData);
}

Terrain::~Terrain() {
	if (texture)
		delete texture;
}