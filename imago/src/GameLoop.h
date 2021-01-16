#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include "TriangleRenderer.h"
#include "ModelRenderer.h"
#include "Model.h"
#include <stdio.h>


class GameLoop
{
public:
	GameLoop();
	virtual ~GameLoop();
	
	void init();
	bool handleInput();
	void update();
	void draw();
	void clean();

private:
	Camera* camera;

	SDL_Window* window;
	SDL_GLContext glContext;
	ModelRenderer* modelRenderer;
	Model* model;

	// Testing
	float x = 0.0f, increment = 0.00005f;
};

