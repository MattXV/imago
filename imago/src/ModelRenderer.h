#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include "Camera.h"
#include "Model.h"
#include "Utils.h"


class ModelRenderer
{
public:
	ModelRenderer(Camera* camera);
	virtual ~ModelRenderer() = default;
	void init();
	void clean();
	void drawModel(Model* model);


private:
	// Shader program info
	unsigned int programId = -1;
	int vertexPositionLocation = -1;

	// Uniforms
	unsigned int modelMatrixLocation = -1, viewMatrixLocation =-1, projectionMatrixLocation = -1, u_Colour = -1;
	

	Camera* camera;
	// Utils
	float pi;


};

