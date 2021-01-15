#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <GL/glew.h>


namespace Utils {
	std::string readFile(const std::string& shaderPath);
	void glCheckError();
}

