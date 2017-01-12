#include "VAOStorage.h"
#include "../RendererResourceManagers/RendererGeometryManager/RendererGeometryManager.h"

//	Default VAOStorage Constructor.
VAOStorage::VAOStorage()
{

}

//	Default VAOStorage Destructor.
VAOStorage::~VAOStorage()
{
	//	
	for (auto currentVAO : VAOs)
	{
		for (auto geometryType = currentVAO->geometryTypeMetaDatas.begin(); geometryType != currentVAO->geometryTypeMetaDatas.end(); geometryType++)
		{
			glDeleteBuffers(1, &geometryType->second->EBO);
			glDeleteBuffers(1, &geometryType->second->vertexVBO);
			glDeleteBuffers(1, &geometryType->second->vertexNormalVBO);
			glDeleteBuffers(1, &geometryType->second->vertexTextureVBO);
		}

		currentVAO->geometryTypeMetaDatas.clear();
		glDeleteVertexArrays(1, &currentVAO->vaoID);
	}
}

//	Add the Geometry Type to the VAO Storage.
void VAOStorage::addGeometryType(std::shared_ptr<GeometryTypeMetaData> newGeometryType)
{
	//	Associate the VAO Meta Data with the Geometry Type.
	std::shared_ptr<VAOMetaData> vaoMetaData = getVAOforGeometry();
	newGeometryType->vaoMetaData = vaoMetaData;

	//	Add the Geometry Type to the VAO.
	vaoMetaData->geometryTypeMetaDatas[newGeometryType->geometryType] = newGeometryType;

	//	Create the Buffers.
	//	Create the Indices Buffer.
	glCreateBuffers(1, &newGeometryType->EBO);
	glNamedBufferData(newGeometryType->EBO, newGeometryType->rendererGeometryData->indicesArray.size() * sizeof(GLuint), newGeometryType->rendererGeometryData->indicesArray.data(), GL_STATIC_DRAW);
	newGeometryType->offsetEBO = 0;

	//	Create the Vertices Buffer.
	glCreateBuffers(1, &newGeometryType->vertexVBO);
	glNamedBufferData(newGeometryType->vertexVBO, newGeometryType->rendererGeometryData->verticesArray.size() * sizeof(Vertex), newGeometryType->rendererGeometryData->verticesArray.data(), GL_STATIC_DRAW);
	newGeometryType->offsetVertexVBO = 0;

	//	
	newGeometryType->vertexNormalVBO = 0;
	newGeometryType->offsetVertexNormalVBO = 0;
	newGeometryType->vertexTextureVBO = 0;
	newGeometryType->offsetVertexTextureVBO = 0;

	//	
	glVertexArrayVertexBuffer(vaoMetaData->vaoID, 0, newGeometryType->vertexVBO, 0, sizeof(Vertex));
	glVertexArrayVertexBuffer(vaoMetaData->vaoID, 1, newGeometryType->vertexVBO, offsetof(Vertex, normal), sizeof(Vertex));
	glVertexArrayVertexBuffer(vaoMetaData->vaoID, 2, newGeometryType->vertexVBO, offsetof(Vertex, color), sizeof(Vertex));

	glVertexArrayVertexBuffer(vaoMetaData->vaoID, 3, newGeometryType->vertexNormalVBO, 0, sizeof(VertexNormalData));
	glVertexArrayVertexBuffer(vaoMetaData->vaoID, 4, newGeometryType->vertexNormalVBO, offsetof(VertexNormalData, bitangent), sizeof(VertexNormalData));

	glVertexArrayVertexBuffer(vaoMetaData->vaoID, 5, newGeometryType->vertexTextureVBO, 0, sizeof(VertexTextureData));
	glVertexArrayVertexBuffer(vaoMetaData->vaoID, 6, newGeometryType->vertexTextureVBO, offsetof(VertexTextureData, textureCoordinates2), sizeof(VertexTextureData));

}

//	Delete the Geometry Type from the VAO Storage.
void VAOStorage::deleteGeometryType(std::shared_ptr<GeometryTypeMetaData> deadGeometryType)
{
	deadGeometryType->vaoMetaData.lock()->geometryTypeMetaDatas.erase(deadGeometryType->geometryType);

	//	Delete the Buffers.
	glDeleteBuffers(1, &deadGeometryType->EBO);
	glDeleteBuffers(1, &deadGeometryType->vertexVBO);
	glDeleteBuffers(1, &deadGeometryType->vertexNormalVBO);
	glDeleteBuffers(1, &deadGeometryType->vertexTextureVBO);

}

//	Get the Available VAO for Geometry.
std::shared_ptr<VAOMetaData> VAOStorage::getVAOforGeometry()
{
	//	
	for (auto currentVAO : VAOs)
	{
		if (currentVAO->geometryTypeMetaDatas.size() < 1)
		{
			return currentVAO;
		}
	}

	//	Construct the new VAO.
	std::shared_ptr<VAOMetaData> newVAO = std::make_shared<VAOMetaData>();
	glCreateVertexArrays(1, &newVAO->vaoID);

	//	Position - as a vec3
	glEnableVertexArrayAttrib(newVAO->vaoID, 0);
	glVertexArrayAttribFormat(newVAO->vaoID, 0, 4, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(newVAO->vaoID, 0, 0);

	//	Normal - as a vec3
	glEnableVertexArrayAttrib(newVAO->vaoID, 1);
	glVertexArrayAttribFormat(newVAO->vaoID, 1, 3, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(newVAO->vaoID, 1, 1);

	//	Color - as a vec4
	glEnableVertexArrayAttrib(newVAO->vaoID, 2);
	glVertexArrayAttribFormat(newVAO->vaoID, 2, 4, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(newVAO->vaoID, 2, 2);

	//	Vertex Tangent - as a vec3
	glEnableVertexArrayAttrib(newVAO->vaoID, 3);
	glVertexArrayAttribFormat(newVAO->vaoID, 3, 3, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(newVAO->vaoID, 3, 3);

	//	Vertex Bitangent - as a vec3
	glEnableVertexArrayAttrib(newVAO->vaoID, 4);
	glVertexArrayAttribFormat(newVAO->vaoID, 4, 3, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(newVAO->vaoID, 4, 4);

	//	Vertex Texture Coordinates 1 - as a vec2
	glEnableVertexArrayAttrib(newVAO->vaoID, 5);
	glVertexArrayAttribFormat(newVAO->vaoID, 5, 2, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(newVAO->vaoID, 5, 5);

	//	Vertex Texture Coordinates 2- as a vec2
	glEnableVertexArrayAttrib(newVAO->vaoID, 6);
	glVertexArrayAttribFormat(newVAO->vaoID, 6, 2, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(newVAO->vaoID, 6, 6);

	//	Add it to the VAOs.
	VAOs.push_back(newVAO);

	glBindVertexArray(0);

	return newVAO;
}
