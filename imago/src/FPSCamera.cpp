#include "FPSCamera.h"

FPSCamera::FPSCamera(SDL_Window* w) :
	window(w)
{

}


void FPSCamera::update() {
	if (keyStates[UP]) {
		position.x += sin(glm::radians(yaw)) * 0.03f;
		position.z -= cos(glm::radians(yaw)) * 0.03f;
	}
	if (keyStates[DOWN]) {
		position.x -= sin(glm::radians(yaw)) * 0.03f;
		position.z += cos(glm::radians(yaw)) * 0.03f;
	}

	// Get Input from mouse and set pitch and yaw accordingly.
	int x, y;
	SDL_GetMouseState(&x, &y);
	float diffX = (x - oldMouseX) * 0.5f;
	float diffY = (y - oldMouseY) * 0.5f;
	yaw += diffX;
	pitch += diffY;
	if (pitch > 20.0f) pitch = 20.0f;
	if (pitch < -20.0f) pitch = -20.0f;

	// Translate and rotate the matrices accordingly
	glm::mat4 matYaw(1.0f), matPitch(1.0f), matRoll(1.0f); // Identity matrices.
	matPitch = glm::rotate(matPitch, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	matRoll = glm::rotate(matRoll, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotate = matPitch * matYaw * matRoll;   // Combine all rotation angles.

	glm::mat4 translate = glm::mat4(1.0f);			  // Translate around.
	translate = glm::translate(translate, -position); 
	viewMatrix = rotate * translate;				  // Combine movement with rotations.

	// Keep Mouse at the centre of the screen.
	SDL_WarpMouseInWindow(window, 320, 240);
	oldMouseX = 320;
	oldMouseY = 240;
}

void FPSCamera::handleInput(SDL_Event& evt)
{
	if (evt.type == SDL_KEYDOWN) {
		switch (evt.key.keysym.scancode) {
		case SDL_SCANCODE_UP:
			keyStates[UP] = true;
			break;
		case SDL_SCANCODE_DOWN:
			keyStates[DOWN] = true;
			break;
		}
	}
	if (evt.type == SDL_KEYUP) {
		switch (evt.key.keysym.scancode) {
		case SDL_SCANCODE_UP:
			keyStates[UP] = false;
			break;
		case SDL_SCANCODE_DOWN:
			keyStates[DOWN] = false;
			break;
		}
	}
}
