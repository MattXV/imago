#include "TriangleRenderer.h"


TriangleRenderer::TriangleRenderer(Camera* camera) :
	camera(camera),
	pi(glm::pi<float>())
{

} 

TriangleRenderer::~TriangleRenderer() {

}


void TriangleRenderer::init() {
	// Create vertex + fragment shader
	programId = glCreateProgram();

	// VERTEX SHADER
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string source = Utils::readFile("resources/shaders/triangle_vertex.shader");
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
	source = Utils::readFile("resources/shaders/triangle_fragment.shader");
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

	vertexPositionLocation = glGetAttribLocation(programId, "aPos");

	// Init vertex data
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), &vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1 * 3 * sizeof(unsigned int), &indexData, GL_STATIC_DRAW);


	Utils::glCheckError();
}

void TriangleRenderer::update() {

}


void TriangleRenderer::draw() {
	glUseProgram(programId);

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject));
	GLCALL(glVertexAttribPointer(vertexPositionLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
	GLCALL(glEnableVertexAttribArray(vertexPositionLocation));

	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject));

	GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	glUseProgram(NULL);
}

void TriangleRenderer::clean() {
	glDeleteProgram(programId);
}

