#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>

#include "TriangleRenderer.h"
#include "ModelRenderer.h"
#include "Model.h"
#include "FPSCamera.h"
#include "Terrain.h"
#include "ApplicationSettings.h"
#include "RenderUtils.h"


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
	// Application 
	SDL_Window* window;
	SDL_GLContext glContext;

	// Scene 
	FPSCamera* camera;
	ModelRenderer* modelRenderer;
	Model* model;
	Texture* texture;
	TriangleRenderer* triangleRenderer;

	Texture* terrainTexture;
	Terrain* terrain;

};

