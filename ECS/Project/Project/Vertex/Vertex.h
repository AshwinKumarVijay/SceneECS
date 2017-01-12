#pragma once

#include "glm\glm.hpp"

struct Vertex 
{
	//	Vertex Position.
	glm::vec4 position = glm::vec4(0.0);

	//	Vertex Normal.
	glm::vec3 normal = glm::vec3(0.0, 1.0, 0.0);

	//	Color of the Vertex - usually just vec4(1.0).
	glm::vec4 color = glm::vec4(1.0);

};


struct VertexTextureData
{
	//	Texture Coordinates - First set.
	glm::vec2 textureCoordinates1;

	//	Texture Coordinates - Second set.
	glm::vec2 textureCoordinates2;
};


struct VertexNormalData
{
	//	Tangent Vector.
	glm::vec3 tangent;

	//	Bitangent Vector.
	glm::vec3 bitangent;

};



