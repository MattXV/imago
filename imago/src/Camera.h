#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


class Camera
{
public:
	Camera();
	virtual ~Camera() = default;

	glm::mat4 getViewMatrix() { return viewMatrix; }
	glm::mat4 getProjectionMatrix() { return projectionMatrix; }
	glm::vec3 getPosition() { return position; }
	void setPosition(float x, float y, float z) { this->position = glm::vec3(x, y, z); }
	glm::vec3 getLookAt() { return lookAt; }
	void updateViewMatrix();

private:

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 position;
	glm::vec3 lookAt;
};

