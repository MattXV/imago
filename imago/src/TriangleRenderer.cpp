#include "TriangleRenderer.h"


TriangleRenderer::TriangleRenderer(Camera* camera) :
	camera(camera),
	pi(glm::pi<float>())
{

} 

TriangleRenderer::~TriangleRenderer() {

}


void TriangleRenderer::init() {

	// Hardcoded vertices just to test it


	// Create vertex + fragment shader
	programId = glCreateProgram();
	// Loads some vertex shader code and attaches it to this class.
	// TODO: use a file to load a shader so it's easier to modify.

	
	// VERTEX SHADER
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string source = Utils::readFile("shaders/vertex.shader");
	const char* shaderSource = source.c_str();

	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE) {
		printf("Could not compile shader :(((( \n %s \n", std::to_string(vertexShader).c_str());
		return;
	}
	glAttachShader(programId, vertexShader);

	
	// FRAGMENT SHADER 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	source = Utils::readFile("shaders/fragment.shader");
	shaderSource = source.c_str();

	glShaderSource(fragmentShader, 1, &shaderSource, NULL);
	glCompileShader(fragmentShader);
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE) {
		printf("Could not compile fragment shader! %d", fragmentShader);
		return;
	}
	glAttachShader(programId, fragmentShader);

	// The following checks whether this vertex shader is compatible with the pixel shader.
	glLinkProgram(programId);
	GLint programSuccess = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE) {
		printf("Could not link shader! \n Program %d \n", programId);
		return;
	}
	glValidateProgram(programId);
	int programValidated = GL_FALSE;
	glGetProgramiv(programId, GL_VALIDATE_STATUS, &programValidated);
	if (programValidated != GL_TRUE) {
		printf("Shader validation failed!\n %d. \n", programId);
		return;
	}

	vertexPositionLocation = glGetAttribLocation(programId, "vertexPosition");
	printf("vertex pos: %d \n", vertexPositionLocation);
	if (vertexPositionLocation == -1) {
		printf("Could not retrieve position for vertexPos2D! \n");
		return;
	}


	// Init vertex data
	glGenBuffers(1, &vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &indexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);


	// Retrieve uniform locations
	modelMatrixLocation = glGetUniformLocation(programId, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(programId, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(programId, "projectionMatrix");
	u_Colour = glGetUniformLocation(programId, "u_Colour");

	Utils::glCheckError();
	printf("Triangle Renderer instantiate successfully! more stonks. \n");
}

void TriangleRenderer::update() {

}


void TriangleRenderer::draw() {
	glUseProgram(programId);

	x += increment;
	increment = (x > 1.0f) ? -increment : increment;
	increment = (x < 0.0f) ? -increment : increment;


	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(90.0f, 45.0f, 45.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, -x * 180.0f / pi, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, x * 180.0f / pi, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, 0 * 180.0f / pi, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, scale);
	camera->updateViewMatrix();

	glUniform4f(u_Colour, 0.3f, 1.0f, 0.3f, 1.0f);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

	// Assign vertex and index data
	glEnableVertexAttribArray(vertexPositionLocation);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject);
	glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayObject);

	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, nullptr);

	glUseProgram(NULL);
}

void TriangleRenderer::clean() {
	glDeleteProgram(programId);
}

