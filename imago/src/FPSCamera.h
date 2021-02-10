#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include <math.h>
#include "Camera.h"
#include "ApplicationSettings.h"


class FPSCamera : public Camera {
public:
	const static int down = 1, up = 0, left = 2, right = 3;
	FPSCamera(SDL_Window* window);
	virtual ~FPSCamera() = default;

	void update();
	void handleInput(SDL_Event& evt);


private:
	float multiplier = 3.0f;
	bool keyStates[4] = { false };
	float yaw = 0.0f, pitch = 0.0f;
	int oldMouseX = 0, oldMouseY = 0;
	SDL_Window* window;
	bool movementEnabled = false;
};
