#include "Terrain.h"

Terrain::Terrain(const std::string& heightmapFile, Texture* t)
	: texture(t)
{
	// Step 1: Load the heightmap file.
	stbi_set_flip_vertically_on_load(1);
	int height = -1, width = -1, channels = -1;
	unsigned char* imageData = stbi_load(heightmapFile.c_str(), &width, &height, &channels, 0);
	if (channels == -1) {
		std::cerr << "could not read image! error: " << stbi_failure_reason() << std::endl;
		return;
	}
	if (!texture)
		texture = new Texture(width, height);


	//SDL_Surface* sdlImage = IMG_Load(heightmapFile.c_str());
	//height = sdlImage->h;
	//width = sdlImage->w;
	//channels = sdlImage->format->BytesPerPixel;
	//unsigned char* imageData = (unsigned char*)sdlImage->pixels;


	// Step 2: Create vertex data from heightmap file.
	std::vector<Vertex> vertices;
	int red, green, blue;
	float x, y, z, u, v;

	float tileHeight = (float)(height - 1), tileWidth = (float)(width - 1);
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {

			red = (int)imageData[(column + row * width) * channels + 0];
			green = (int)imageData[(column + row * width) * channels + 1];
			blue = (int)imageData[(column + row * width) * channels + 2];


			// The following creates vertex data from the height value sampled from the image.
			x = ((float)column / tileWidth) * tileSize; // the subtraction centres the tile around 0
			y = ((float)(red + green + blue) / 255.0f - 1.0f) * tileScaling;
			z = ((float)row / tileHeight) * tileSize;
			u = (float)column / tileWidth;
			v = (float)row / tileHeight;
			//v = (float)(tileHeight - row) / tileHeight;

			vertices.emplace_back(x, y, z, u, v);
		}
	}

	// Create index data
	std::vector<unsigned int> indices;
	unsigned int c, n;
	for (int row = 0; row < height - 1; row++) { 
		for (int column = 0; column < width - 1; column++) {

			c = row * width + column;
			n = (row + 1) * width + column;

			// Indices go counter-clockwise with GL_TRIANGLES!
			indices.push_back(c);     //						               `width`
			indices.push_back(n);	  // First triangle  row 0  c--c+1 --------------
			indices.push_back(c + 1); //				  	    | /| /|    
									  //                        |/ |/ |  		
			indices.push_back(c + 1); //                 row 1  n--n+1---------------   
			indices.push_back(n);  	  //                	    | /|  
			indices.push_back(n + 1); //					    |/ |   
									  //				 row 2  *--*  		
		}							  //					    |  |
	}
	indexCount = indices.size();

	// Transfer these vectors containing our mesh data to OpenGL buffers.
	vboLocation = RenderUtils::createVBO(vertices);
	iboLocation = RenderUtils::createIBO(indices);

	stbi_image_free(imageData);
	//SDL_free(sdlImage);
}

Terrain::~Terrain() {
	if (texture)
		delete texture;
}