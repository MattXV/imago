#include "FPSCamera.h"

FPSCamera::FPSCamera(SDL_Window* w)
	: Camera(w)
{

}


void FPSCamera::update() {
	if (keyStates[FPSCamera::up]) {
		position.z -= cos(glm::radians(yaw)) * multiplier;
		position.x += sin(glm::radians(yaw)) * multiplier;
	}
	if (keyStates[FPSCamera::down]) {
		position.x -= sin(glm::radians(yaw)) * multiplier;
		position.z += cos(glm::radians(yaw)) * multiplier;
	}
	if (keyStates[FPSCamera::left]) {
		position.x -= sin(glm::radians(yaw)) * multiplier;
		//position.z -= cos(glm::radians(pitch)) * 0.03f;
	}
	if (keyStates[FPSCamera::right]) {
		position.x += sin(glm::radians(yaw)) * multiplier;
		//position.z -= cos(glm::radians(pitch)) * 0.03f;
	}


	// Get Input from mouse and set pitch and yaw accordingly.
	if (movementEnabled) {

		int x, y;
		SDL_GetMouseState(&x, &y);
		float diffX = (x - oldMouseX) * 0.5f;
		float diffY = (y - oldMouseY) * 0.5f;
		yaw += diffX;
		pitch += diffY;
		if (pitch > 90.0f) pitch = 90.0f;
		if (pitch < -90.0f) pitch = -90.0f;

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
		SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
		oldMouseX = windowWidth / 2;
		oldMouseY = windowHeight / 2;
	}
}


void FPSCamera::handleInput(SDL_Event& evt)
{
	if (evt.type == SDL_KEYDOWN) {
		switch (evt.key.keysym.scancode) {
		case SDL_SCANCODE_W:
			keyStates[FPSCamera::up] = true;
			break;
		case SDL_SCANCODE_S:
			keyStates[FPSCamera::down] = true;
			break;
		case SDL_SCANCODE_A:
			keyStates[FPSCamera::left] = true;
			break;
		case SDL_SCANCODE_D:
			keyStates[FPSCamera::right] = true;
			break;
		case SDL_SCANCODE_TAB:
			movementEnabled = !movementEnabled;
			break;
		}
	}
	if (evt.type == SDL_KEYUP) {
		switch (evt.key.keysym.scancode) {
		case SDL_SCANCODE_W:
			keyStates[FPSCamera::up] = false;
			break;
		case SDL_SCANCODE_S:
			keyStates[FPSCamera::down] = false;
			break;
		case SDL_SCANCODE_A:
			keyStates[FPSCamera::left] = false;
			break;
		case SDL_SCANCODE_D:
			keyStates[FPSCamera::right] = false;
			break;

		}
	}
}
