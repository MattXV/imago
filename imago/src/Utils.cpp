#include "Utils.h"


std::string Utils::readFile(const std::string& shaderPath) {
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
