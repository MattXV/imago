#include "RenderUtils.h"

unsigned int RenderUtils::createVBO(std::vector<Vertex>& vertices)
{
    unsigned int newBuffer;
    GLCALL(glCreateBuffers(1, &newBuffer));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, newBuffer));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), (void*)&vertices[0], GL_STATIC_DRAW));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, NULL));
    return newBuffer;
}

unsigned int RenderUtils::createVBO(std::vector<float>& vertices)
{
    unsigned int newBuffer;
    GLCALL(glCreateBuffers(1, &newBuffer));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, newBuffer));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), (void*)&vertices[0], GL_STATIC_DRAW));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, NULL));
    return newBuffer;
}

unsigned int RenderUtils::createIBO(std::vector<unsigned int>& indices) {
    unsigned int newBuffer;
    GLCALL(glGenBuffers(1, &newBuffer));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newBuffer));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), (void*)&indices[0], GL_STATIC_DRAW));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL));
    return newBuffer;
}

