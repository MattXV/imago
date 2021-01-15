#include "Model.h"

Model::Model(std::string modelFile) :
	file(modelFile),
	position(glm::vec3(0, 0, 0)),
	rotation(glm::vec3(0, 45, 0)),
	scale(1.0f, 1.0f, 1.0f)
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

	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		std::vector<float> vertices;
		std::vector<float> indices;

		for (int j = 0; j < mesh->mNumVertices; j++) {
			// Extract vertices from the mesh object.
			const aiVector3D* pos = &mesh->mVertices[j];
			vertices.push_back(pos->x);
			vertices.push_back(pos->y);
			vertices.push_back(pos->z);
		}

		for (int j = 0; j < mesh->mNumFaces; j++) {
			// Extract corresponding indices.
			aiFace* face = &mesh->mFaces[j];
			if (face->mNumIndices != 3) {
				continue; // Only triangular faces!
			}

			for (int v = 0; i < 3; v++) {
				indices.push_back(face->mIndices[v]);
			}
		}
		// Move data to OpenGL buffers
		unsigned int vbo, ibo;
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ibo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

		vertexBufferObjects.push_back(vbo);
		indexBufferObjects.push_back(ibo);
		indexCounts.push_back(indices.size());
	}



}
