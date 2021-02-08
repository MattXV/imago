#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include "Camera.h"
#include "Model.h"
#include "Terrain.h"
#include "Utils.h"
#include "SkyDome.h"



class ModelRenderer
{
public:
	ModelRenderer(Camera* camera);
	virtual ~ModelRenderer() = default;
	void init();
	void clean();
	void drawModel(Model* model);
	void renderTerrain(Terrain* terrain);
	void renderSkyDome(SkyDome* skydome, float x);

private:
	// Shader program info
	unsigned int programId = -1;
	int vertexPositionLocation = -1;

	// Shader parameter locations
	unsigned int modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, uvLocation;
	int textureSamplerLocation = -1;

	Camera* camera;
	// Utils
	float pi;
};

