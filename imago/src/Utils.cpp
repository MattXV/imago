#include "Utils.h"


const std::string Utils::readFile(const std::string& shaderPath) {
	std::ifstream shaderFile(shaderPath);
	std::stringstream shaderSource;

	std::string line;
	if (shaderFile.is_open()) {
		while (std::getline(shaderFile, line)) {
			shaderSource << line << std::endl;
		}
		shaderFile.close();
	}
	else {
		printf("[ERROR] Could not open file: %s \n", shaderPath.c_str());
	}
	return shaderSource.str();
}

void Utils::glCheckError() {
	while (GLenum error = glGetError()) {
		printf("[OpenGL Error]: %d \n", error);
	}
}

void Utils::glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool Utils::glLogError(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError()) {
		printf("[OPENGL ERROR]: %d \n", error);
		printf("Function: %s, in file %s, in line %d", function, file, line);
		return false;
	}
	return true;
}

std::string Utils::StemPath(std::string path)
{
	const rsize_t pos = path.find_last_of('.');
	std::string stem = path.substr(0, pos);
	return stem;
}
