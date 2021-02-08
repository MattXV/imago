#pragma once

#include <string>
#include <vector>
#include "Texture.h"
#include "externals/stb_image/stb_image.h"
#include <glm/glm.hpp>
#include "Utils.h"
#include "RenderUtils.h"


class Terrain
{
public:
	Terrain(const std::string& heightmapFile, Texture* texture = nullptr);
	virtual ~Terrain();

	const unsigned int& getVBOLocation() { return vboLocation; }
	const unsigned int& getIBOLocation() { return iboLocation; }
	const unsigned int& getindexCount() { return indexCount; }
	const unsigned int& getIndexCount() { return indexCount; }
	Texture* getTexture() { return texture; }

private:
	float tileScaling = 0.5f, tileSize = 4.0f;
	Texture* texture;
	unsigned int vboLocation = 0, iboLocation = 0;
	unsigned int indexCount = 0;
};