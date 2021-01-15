#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <string>


class Model
{
	// add model renderer as a friend
public:
	Model(std::string modelFile);
	virtual ~Model() = default;

private:	
	std::string file;
	glm::vec3 position, rotation, scale;

	std::vector<unsigned int> vertexBufferObjects, indexBufferObjects;
	std::vector<int> indexCounts;
};

