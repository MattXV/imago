#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <iostream>
#include <vector>
#include <string>

#include "Texture.h"
#include "Utils.h"

class Model
{
public:
	Model(std::string modelFile);
	~Model();

	const std::vector<unsigned int>& getVbos() { return vertexBufferObjects; }
	const std::vector<unsigned int>& getIbos() { return indexBufferObjects; }
	const std::vector<unsigned int>& getUvos() { return uvBufferObjects; }
	const std::vector<int>& getIndexCounts() { return indexCounts; }
	glm::vec3& getPosition() { return position; }
	void setPosition(glm::vec3 newPosition) { position = newPosition; }
	glm::vec3& getTranslation() { return translation; };
	void  setTranslation(glm::vec3 newScale) { scale = newScale; }
	glm::vec3& getRotation() { return rotation; }
	void setRotation(glm::vec3 newRotation) { rotation = newRotation; }
	glm::vec3& getScale() { return scale; }
	void setScale(glm::vec3 newScale) { scale = newScale; }

	//Texture
	void setTexture(Texture* t) { texture = t; }
	Texture* getTexture() { return texture; }
	unsigned int getTextureId() { return texture->getTextureId(); }
private:	

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(90.0f, 45.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	
	std::string file;
	bool hasUVCoords = false;
	unsigned int vertexArrayObject = 0;
	std::vector<unsigned int> vertexBufferObjects, indexBufferObjects, uvBufferObjects;
	std::vector<int> indexCounts;
	Texture* texture;
	
};

