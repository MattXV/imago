#pragma once

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include "Utils.h"
#include "Camera.h"
#include <math.h>
#include <gtc/type_ptr.hpp>



static GLfloat vertexData[] = {
	-0.5f,  0.0f, 1.0f,
	 0.0f, -0.5f, 1.0f,
	 0.0f,  0.0f, 1.0f,
   	 0.5f,  0.0f, 1.0f,
	 0.0f,  0.5f,  1.0f
};
static GLuint indexData[] = {
	0, 1, 2,
	2, 3, 4
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
	GLuint programId = 0;
	GLint vertexPositionLocation = -1;
	GLuint vertexArrayObject = 0;
	GLuint indexArrayObject = 0;
	int modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, u_Colour = - 1;

	// Utils
	float pi;

	// Test
	float increment = 0.0005f;
	float x = 0.0f;
};

