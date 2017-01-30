#pragma once

#include <vector>
#include <memory>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"

#include "../Vertex/Vertex.h"
#include "../ResourceData.h"


class GeometryData : public ResourceData
{

public:


	//	GeometryData Constructor for Vertex Data.
	GeometryData(const GLenum & newGeometryDrawType, const std::vector<int> & newGeometryIndices, const std::vector<Vertex> & newGeometryVertices);

	//	GeometryData Constructor for Vertex Data and Normal Data.
	GeometryData(const GLenum & newGeometryDrawType, const std::vector<int> & newGeometryIndices, const std::vector<Vertex> & newGeometryVertices, const std::vector<VertexNormalData> & newGeometryNormalData);

	//	GeometryData Constructor with Vertex Data and Texture Coordinates.
	GeometryData(const GLenum & newGeometryDrawType, const std::vector<int> & newGeometryIndices, const std::vector<Vertex> & newGeometryVertices, const std::vector<VertexTextureData> & newGeometryTextureData);

	//	GeometryData Constructor for Vertex Data and Normal Data and Texture Coordinates.
	GeometryData(const GLenum & newGeometryDrawType, const std::vector<int> & newGeometryIndices, const std::vector<Vertex> & newGeometryVertices, const std::vector<VertexNormalData> & newGeometryNormalData, const std::vector<VertexTextureData> & newGeometryTextureData);

	//	GeometryData Constructor for Vertex Data and Normal Data and Texture Coordinates.
	GeometryData(const unsigned int & newGeometryDescription, const GLenum & newGeometryDrawType, const std::vector<int> & newGeometryIndices, const std::vector<Vertex> & newGeometryVertices, const std::vector<VertexNormalData> & newGeometryNormalData, const std::vector<VertexTextureData> & newGeometryTextureData);

	//	Default GeometryData Destructor.
	virtual ~GeometryData();

	//	Return the Geometry Draw Type.
	GLenum getGeometryDrawType() const;

	//	View the indices associated with the Geometry.
	const std::vector<int> & viewGeometryIndices() const;

	//	View the vertices associated with the Geometry.
	const std::vector<Vertex> & viewGeometryVertices() const;

	//	View the associated Geometry Normal Data.
	const std::vector<VertexNormalData> & viewGeometryNormalData() const;

	//	View the associated Geometry Texture Data.
	const std::vector<VertexTextureData> & viewGeometryTextureData() const;

	//	
	unsigned int getHasVertexData() const;
	unsigned int getHasVertexTextureData() const;
	unsigned int getHasVertexTangentBitangentData() const;

private:

	//	The Geometry Data Type.
	unsigned int hasGeometryVertexData = 0;
	unsigned int hasGeometryVertexTextureData = 0;
	unsigned int hasGeometryVertexTangentBitangentData = 0;


	//	The type of geometry represented.
	GLenum geometryDrawType;

	//	The indices of this geometry - into the vertices.
	std::vector<int> geometryIndices;

	//	The Vertices of this geometry.
	std::vector<Vertex> geometryVertices;

	//	The Vertex Texture Data of this Geometry.
	std::vector<VertexTextureData> geometryTextureData;

	//	The Vertex Normal Data of this Geometry.
	std::vector<VertexNormalData> geometryNormalData;
};

