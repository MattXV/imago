#pragma once

#include "Texture.h"
#include "RenderUtils.h"
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <math.h>
#include <vector>


class SkyDome
{
public:
	SkyDome(Texture* texture = nullptr, const float radius = 50.0f, const unsigned int resolution = 16);
	virtual ~SkyDome();

	unsigned int& getVBOLocation() { return vbo; }
	unsigned int& getIBOLocation() { return ibo; }
	unsigned int& getUVBOLocation() { return uvbo; }
	unsigned int& getIndexCount() { return indexCount; }
	Texture* getTexture() { return texture; }
	

private:
	const float radius;
	const unsigned int resolution;
	unsigned int vbo = 0, ibo = 0, uvbo = 0;

	unsigned int indexCount;

	Texture* texture;
};

