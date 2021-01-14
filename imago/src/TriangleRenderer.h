#pragma once

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <string>


static GLfloat vertexData[] = {
	-0.5f, 0.0f,
	0.0f, -0.5f,
	0.0f, 0.0f,
	0.5f, 0.0f,
	0.0f, 0.5f
};
static GLuint indexData[] = {
	0, 1, 2,
	2, 3, 4
};


static void GLCheckError() {
	while (GLenum error = glGetError()) {
		printf("[OpenGL Error]: %d \n", error);
	}
}

class TriangleRenderer
{
public:

	
	TriangleRenderer();
	virtual ~TriangleRenderer();

	void init();
	void update();
	void draw();
	void clean();


private:

	GLuint programId = 0;
	GLint vertexPos2DLocation = -1;
	GLuint vertexArrayObject = 0;
	GLuint indexArrayObject = 0;

};

