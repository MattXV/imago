#pragma once

#include <glm/glm.hpp>
#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include "ApplicationSettings.h"


class Camera
{
public:
	Camera(SDL_Window* window);
	virtual ~Camera() = default;

	glm::mat4 getViewMatrix() { return viewMatrix; }
	glm::mat4 getProjectionMatrix() { return projectionMatrix; }
	glm::vec3 getPosition() { return position; }
	void setPosition(float x, float y, float z) { this->position = glm::vec3(x, y, z); }
	glm::vec3 getLookAt() { return lookAt; }
	void updateViewMatrix();
	virtual void update() {}
	virtual void handleInput(SDL_Event&) {}

protected:
	SDL_Window* window;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 position;
	glm::vec3 lookAt;
};
