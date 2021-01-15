#pragma once
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include "TriangleRenderer.h"


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
	TriangleRenderer* triangleRenderer;
};

