#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <string>

#include "Utils.h"

class Model
{
	// add model renderer as a friend
public:
	Model(std::string modelFile);
	virtual ~Model() = default;

	const std::vector<unsigned int>& getVbos() { return vertexBufferObjects; }
	const std::vector<unsigned int>& getIbos() { return indexBufferObjects; }
	const std::vector<int>& getIndexCounts() { return indexCounts; }

	// Getters/setters
	glm::vec3& getPosition() { return position; }
	void setPosition(glm::vec3 newPosition) { position = newPosition; }
	glm::vec3& getTranslation() { return translation; };
	void  setTranslation(glm::vec3 newScale) { scale = newScale; }
	glm::vec3& getRotation() { return rotation; }
	void setRotation(glm::vec3 newRotation) { rotation = newRotation; }
	glm::vec3& getScale() { return scale; }
	void setScale(glm::vec3 newScale) { scale = newScale; }


private:	
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(90.0f, 45.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	
	std::string file;

	std::vector<unsigned int> vertexBufferObjects, indexBufferObjects;
	std::vector<int> indexCounts;


};

