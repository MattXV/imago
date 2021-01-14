#include "TriangleRenderer.h"

TriangleRenderer::TriangleRenderer() {

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
	const GLchar* vertexShaderSource[] =
	{
		"#version 330 core\nin vec2 vertexPos2D; "
		"void main() \n"
		"{ gl_Position = vec4(vertexPos2D.x, vertexPos2D.y, 0, 1 ); }"
	};
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
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
	const GLchar* fragmentShaderSource[] = {
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 fragmentColor; \n"
		"void main() \n"
		"{ fragmentColor = vec4( 1.0, 0.0, 0.0, 1.0); }"
	};
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
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

	vertexPos2DLocation = glGetAttribLocation(programId, "vertexPos2D");
	printf("vertex pos: %d \n", vertexPos2DLocation);
	if (vertexPos2DLocation == -1) {
		printf("Could not retrieve position for vertexPos2D! \n");
		return;
	}


	// Init vertex data
	glGenBuffers(1, &vertexArrayObject);
	glEnableVertexAttribArray(vertexPos2DLocation);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject);
	GLCheckError();
	glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	GLCheckError();

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);


	glGenBuffers(1, &indexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);


	glDeleteProgram(vertexShader);
	glDeleteProgram(fragmentShader);
	printf("Triangle Renderer instantiate successfully! more stonks. \n");
}

void TriangleRenderer::update() {

}


void TriangleRenderer::draw() {
	glUseProgram(programId);
	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, nullptr);

	glUseProgram(NULL);
}

void TriangleRenderer::clean() {
	glDeleteProgram(programId);

}




