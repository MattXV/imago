#pragma once

#include <gl/glew.h>
#include <vector>
#include "Utils.h"

struct Vertex {
	Vertex(float xPos, float yPos, float zPos, float uCoord, float vCoord) {
		x = xPos;
		y = yPos;
		z = zPos;
		u = uCoord;
		v = vCoord;
	}

	float x, y, z, u, v;
};


namespace RenderUtils
{
	unsigned int createVBO(std::vector<Vertex>& vertices);
	unsigned int createVBO(std::vector<float>& vertices);
	unsigned int createIBO(std::vector<unsigned int>& indices);
};
