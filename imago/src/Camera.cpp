#include "Camera.h"

Camera::Camera(SDL_Window* window) 
	: window(window)
{
	float fov = 45.0f;
	float aspectRatio = 640.0f / 480.0f;
	float near = 0.1f;
	float far = 900.0f;

	this->position = glm::vec3(0.0f, 0.0f, -5.0f);
	this->lookAt = glm::vec3(0.0f, 0.0f, 1.0f);

	projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
	updateViewMatrix();
}


void Camera::updateViewMatrix() {
	viewMatrix = glm::lookAt(position, lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
}