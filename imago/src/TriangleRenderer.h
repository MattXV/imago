#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include "Utils.h"
#include "Camera.h"
#include <math.h>
#include <glm/gtc/type_ptr.hpp>



static float vertexData[] = {
	-0.5f,  0.0f,
	 0.5f,  0.0f,
	 0.0f,  0.5f
};
static unsigned int indexData[] = {
	0, 1, 2
};


class TriangleRenderer
{
public:
	TriangleRenderer(Camera* camera);
	virtual ~TriangleRenderer();

	void init();
	void update();
	void draw();
	void clean();

private:
	Camera* camera;

	// OpenGL locations
	unsigned int programId = 0;
	int vertexPositionLocation = -1;
	unsigned int vertexBufferObject = 0, indexBufferObject = 0, vertexArrayObject = 0;
	int modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, u_Colour = - 1;

	// Utils
	float pi;

	// Test
	float increment = 0.0005f;
	float x = 0.0f;
};
