#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCALL(x) Utils::glClearError(); x; ASSERT(Utils::glLogError(#x, __FILE__, __LINE__))


namespace Utils {
	const std::string readFile(const std::string& shaderPath);
	void glCheckError();
	void glClearError();
	bool glLogError(const char* function, const char* file, int line);
	std::string StemPath(std::string path);
}

