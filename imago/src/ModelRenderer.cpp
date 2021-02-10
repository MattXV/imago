#include "ModelRenderer.h"

ModelRenderer::ModelRenderer(Camera* c) :
	camera(c),
	pi(glm::pi<float>())
{

}

void ModelRenderer::init() {
	// Init Shaders:

	// Vertex Shader
	programId = glCreateProgram();
	Utils::glCheckError();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string shaderString = Utils::readFile("resources/shaders/vertex.shader");
	const char* shaderSource = shaderString.c_str();
	glShaderSource(vertexShader, 1, &shaderSource, nullptr);
	glCompileShader(vertexShader);
	int success = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		printf("[ERROR] Could not compile vertex shader in Model Renderer!\n");
		return;
	}
	glAttachShader(programId, vertexShader);


	// Fragment Shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderString = Utils::readFile("resources/shaders/fragment.shader");
	shaderSource = shaderString.c_str();
	glShaderSource(fragmentShader, 1, &shaderSource, nullptr);
	glCompileShader(fragmentShader);
	success = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		printf("[ERROR] Could not compile fragment shader in Model Renderer! \n");
		return;
	}
	glAttachShader(programId, fragmentShader);

	// Link and Validate Program
	glLinkProgram(programId);
	success = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		printf("[ERROR] Could not link program in Model Renderer! \n");
		return;
	}
	glValidateProgram(programId);
	success = GL_FALSE;
	glGetProgramiv(programId, GL_VALIDATE_STATUS, &success);
	if (!success) {
		printf("[ERROR] Model Renderer: Validation failed! \n");
		return;
	}

	// Retrieve attribute and uniform locations
	// Vertex Shader
	vertexPositionLocation = glGetAttribLocation(programId, "vertexPosition");
	modelMatrixLocation = glGetUniformLocation(programId, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(programId, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(programId, "projectionMatrix");
	uvLocation = glGetAttribLocation(programId, "uv");

	// Fragment Shader
	textureSamplerLocation = glGetUniformLocation(programId, "textureSampler");
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ModelRenderer::clean() {
	glDeleteProgram(programId);
}


void ModelRenderer::drawModel(Model* model) {
	glUseProgram(programId);

	// Create and manipulate the Model Matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix
	modelMatrix = glm::rotate(modelMatrix, model->getRotation().x * 180.0f / pi, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, model->getRotation().y * 180.0f / pi, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, model->getRotation().z * 180.0f / pi, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, model->getTranslation());
	modelMatrix = glm::scale(modelMatrix, model->getScale());

	// Set Uniforms/Attributes
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

	// Assign data to VBO and IBO
	std::vector<unsigned int> vbos = model->getVbos();
	std::vector<unsigned int> ibos = model->getIbos();
	std::vector<unsigned int> uvos = model->getUvos();
	std::vector<int> counts = model->getIndexCounts();
	
	for (int i = 0; i < vbos.size(); ++i) {
		// Vertex positions
		glEnableVertexAttribArray(vertexPositionLocation);
		glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
		glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
		
		//UV coordinates
		glEnableVertexAttribArray(uvLocation);
		glBindBuffer(GL_ARRAY_BUFFER, uvos[i]);
		glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(textureSamplerLocation, 0);
		glBindTexture(GL_TEXTURE_2D, model->getTextureId());

		// Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[i]);

		glDrawElements(GL_TRIANGLES, counts[i], GL_UNSIGNED_INT, nullptr);
	}

	glUseProgram(NULL);
}

void ModelRenderer::renderTerrain(Terrain* terrain)
{
	glUseProgram(programId);

	glm::vec3 translation(glm::vec3(0, -150, 0)), rotation(glm::vec3(0, 0, 0)), scale(glm::vec3(100, 100, 100));

	glm::mat4 modelMatrix = RenderUtils::createModelMatrix(rotation, translation, scale);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

	// Set Array data
	glEnableVertexAttribArray(vertexPositionLocation);
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, terrain->getVBOLocation()));
	GLCALL(glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));

	// UV buffer
	glEnableVertexAttribArray(uvLocation);
	GLCALL(glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u)));

	// Set texture
	glActiveTexture(GL_TEXTURE0);
	GLCALL(glUniform1i(textureSamplerLocation, 0));
	GLCALL(glBindTexture(GL_TEXTURE_2D, terrain->getTexture()->getTextureId()));

	// Set index buffer and draw with them
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain->getIBOLocation()));
	glDrawElements(GL_TRIANGLES, terrain->getIndexCount(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisableVertexAttribArray(vertexPositionLocation);
	glUseProgram(NULL);
}

void ModelRenderer::renderSkyDome(SkyDome* skydome, float x)
{
	glUseProgram(programId);
	glm::vec3 translation(glm::vec3(1.0f, 1.0f, 1.0f)), rotation(glm::vec3(0, 0, 0)), scale(glm::vec3(10, 10, 10));
	glm::mat4 modelMatrix(glm::mat4(1.0f));

	//translation = camera->getPosition();
	modelMatrix = glm::rotate(modelMatrix, rotation.x * 180.0f / pi, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y * 180.0f / pi, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z * 180.0f / pi, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::scale(modelMatrix, scale);

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

	// vertex data
	glEnableVertexAttribArray(vertexPositionLocation);
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, skydome->getVBOLocation()));
	GLCALL(glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
	// UV data
	glEnableVertexAttribArray(uvLocation);
	GLCALL(glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u)));

	// Set texture
	glActiveTexture(GL_TEXTURE0);
	GLCALL(glUniform1i(textureSamplerLocation, 0));
	GLCALL(glBindTexture(GL_TEXTURE_2D, skydome->getTexture()->getTextureId()));

	// Set index buffer and draw with them
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skydome->getIBOLocation()));
	glDrawElements(GL_TRIANGLES, skydome->getIndexCount(), GL_UNSIGNED_INT, NULL);



	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glDisableVertexAttribArray(vertexPositionLocation);
	glUseProgram(NULL);
}


