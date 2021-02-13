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

template<typename T>
struct Colour {
	Colour(T red, T green, T blue, T alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	T r, g, b, a;
};

namespace RenderUtils
{
	unsigned int createVBO(std::vector<Vertex>& vertices);
	unsigned int createVBO(std::vector<float>& vertices);
	unsigned int createIBO(std::vector<unsigned int>& indices);
};
