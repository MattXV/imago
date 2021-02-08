#include "Model.h"

Model::Model(std::string modelFile) :
	file(modelFile),
	position(glm::vec3(0, 0, 0)),
	rotation(glm::vec3(0, 45, 0)),
	scale(1.0f, 1.0f, 1.0f),
	texture(nullptr)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		file,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);
	if (!scene) {
		printf("[ERROR] Could not load mesh file!\nFile: %s \n", file.c_str());
		return;
	}

	for (int i = 0; i < (int)scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		std::vector<float> uvMap;

		for (int j = 0; j < (int)mesh->mNumVertices; j++) {
			// Extract vertices from the mesh object.
			const aiVector3D* pos = &mesh->mVertices[j];
			vertices.push_back(pos->x);
			vertices.push_back(pos->y);
			vertices.push_back(pos->z);

			if (mesh->HasTextureCoords(0)) {
				hasUVCoords = true;
				aiVector3D textureCoords = mesh->mTextureCoords[0][j];
				uvMap.push_back(textureCoords.x);
				uvMap.push_back(textureCoords.y);
			}
		}

		for (int j = 0; j < (int)mesh->mNumFaces; j++) {
			// Extract corresponding indices.
			aiFace* face = &mesh->mFaces[j];
			if (face->mNumIndices != 3) {
				continue; // Only triangular faces!
			}
			indices.push_back((unsigned int)face->mIndices[0]);
			indices.push_back((unsigned int)face->mIndices[1]);
			indices.push_back((unsigned int)face->mIndices[2]);
		}

		// Move data to OpenGL buffers
		unsigned int vbo, ibo, uvo;
		// VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
		// IBO
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		// UV Coordinates
		if (hasUVCoords) {
			glGenBuffers(1, &uvo);
			glBindBuffer(GL_ARRAY_BUFFER, uvo);
			glBufferData(GL_ARRAY_BUFFER, uvMap.size() * sizeof(float), &uvMap[0], GL_STATIC_DRAW);
			uvBufferObjects.push_back(uvo);
		}

		vertexBufferObjects.push_back(vbo);
		indexBufferObjects.push_back(ibo);
		indexCounts.push_back((int)indices.size());
	}

	// Create Vertex Array Object
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
}

Model::~Model()
{

}

