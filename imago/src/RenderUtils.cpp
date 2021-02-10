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

glm::mat4 RenderUtils::createModelMatrix(glm::vec3& rotation, glm::vec3& translation, glm::vec3& scale)
{
    glm::mat4 modelMatrix(1.0f);

    modelMatrix = glm::rotate(modelMatrix, rotation.x * 180.0f / pi, glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, rotation.y * 180.0f / pi, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, rotation.z * 180.0f / pi, glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, translation);
    modelMatrix = glm::scale(modelMatrix, scale);

    return modelMatrix;
}

