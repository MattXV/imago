#include "SkyDome.h"

SkyDome::SkyDome(Texture* t, const float rad, const unsigned int res) :
	texture(t)
	, radius(rad)
	, resolution(res)
{
	if (!texture)
		texture = new Texture(resolution, resolution, Colour<unsigned char>(255, 255, 255, 255));
	
	float constexpr pi = glm::pi<float>();
	const float azimuthStep = (2.0f * pi) / (float)(resolution - 1);
	const float elevationStep = pi / (float)(resolution - 1);

	// Here a sphere is created using cartesian coordinates.
	// With the resolution, the slices and sectors of the sphere are determined.
	// The slices are triangulated to generate a mesh for the skydome.
	// 
	// x = (radius * cos(phi)) * cos(theta)
	// z = (radius * cos(phi)) * sin(theta)
	// y = radius * sin(phi)
	// 
	// theta = 2 * pi * (azimuthStep / totalAzimuthSteps) -> inclination
	// phi = pi/2 - (pi * elevationStep / totalElevationSteps) -> azimuth

	std::vector<Vertex> vertices;
	float x, y, z, u, v;
	float theta, phi;
	for (int latitude = 0; latitude < resolution + 1; latitude++) {
		for (int longitude = 0; longitude < resolution + 1; longitude++) {
		
			// Calculate inclination and azimuth angles.
			theta = pi / 2.0f - longitude * elevationStep;

			// Vertex position
			phi = latitude * azimuthStep;
			x = (radius * cosf(theta)) * cosf(phi);
			z = (radius * cosf(theta)) * sinf(phi);
			y = radius * sinf(theta);

			// UV coordinates
			u = (float)latitude / (float)resolution;
			v = (float)longitude / (float)resolution;

			vertices.emplace_back(x, y, z, u, v);
		}
	}

	// Indices
	//
	// Generate indices by addressing triangles inside each slice and sector.
	// Triangles are indexed *counter-clockwise*, starting from the top-left.
	//
	// C -- C+1    -> C is the index on the current elevation level
	// |  / |
	// | /  |
	// N -- N+1    -> N is the in dex on the next elevation level
	// 
	//
	std::vector<unsigned int> indices;
	unsigned int c, n;
	for (int latitude = 0; latitude < resolution - 1; latitude++) {

		c = latitude * (resolution + 1); // beginning of the current level
		n = c + resolution + 1;		     //	beginning of the next level

		//						Note that we're incrementing n and c too here!
		for (int longitude = 0; longitude < resolution - 1; longitude++, c++, n++) { 
			if (longitude != 0) {
				indices.push_back(c);
				indices.push_back(n);
				indices.push_back(c + 1);
			}
			if (longitude != resolution - 1) {
				indices.push_back(c + 1);
				indices.push_back(n);
				indices.push_back(n + 1);
			}
		}
	}

	vbo = RenderUtils::createVBO(vertices);
	ibo = RenderUtils::createIBO(indices);

	indexCount = indices.size();
}

SkyDome::~SkyDome() {
	if (texture)
		delete texture;
}

