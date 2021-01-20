#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include <math.h>
#include "Camera.h"

#define UP 0
#define DOWN 1

class FPSCamera : public Camera {
public:
	FPSCamera(SDL_Window* window);
	virtual ~FPSCamera() = default;

	void update();
	void handleInput(SDL_Event& evt);
private:
	bool keyStates[2] = { false, false };
	float yaw = 0.0f, pitch = 0.0f;
	int oldMouseX = 0, oldMouseY = 0;
	SDL_Window* window;
};
