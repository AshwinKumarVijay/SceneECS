#include "GeometryData.h"

//	Default GeometryData Constructor.
GeometryData::GeometryData(const GLenum & newGeometryDrawType, const std::vector<int>& newGeometryIndices, const std::vector<Vertex>& newGeometryVertices)
{
	hasGeometryVertexData = 1;
	hasGeometryVertexTextureData = 0;
	hasGeometryVertexTangentBitangentData = 0;

	//	Copy over the Geometry Draw Type.
	geometryDrawType = newGeometryDrawType;

	//	Copy over the Geometry Indices.
	geometryIndices = newGeometryIndices;

	//	Copy over the Geometry Vertices.
	geometryVertices = newGeometryVertices;
}

//	
GeometryData::GeometryData(const GLenum & newGeometryDrawType, const std::vector<int>& newGeometryIndices, const std::vector<Vertex> & newGeometryVertices, const std::vector<VertexNormalData>& newGeometryNormalData)
{

	hasGeometryVertexData = 1;
	hasGeometryVertexTextureData = 0;
	hasGeometryVertexTangentBitangentData = 1;

	//	Copy over the Geometry Draw Type.
	geometryDrawType = newGeometryDrawType;

	//	Copy over the Geometry Indices.
	geometryIndices = newGeometryIndices;

	//	Copy over the Geometry Vertices.
	geometryVertices = newGeometryVertices;

	//	Copy over the Geometry Normal Data.
	geometryNormalData = newGeometryNormalData;
}

//	
GeometryData::GeometryData(const GLenum & newGeometryDrawType, const std::vector<int>& newGeometryIndices, const std::vector<Vertex> & newGeometryVertices, const std::vector<VertexTextureData> & newGeometryTextureData)
{
	//	
	hasGeometryVertexData = 1;
	hasGeometryVertexTextureData = 1;
	hasGeometryVertexTangentBitangentData = 0;

	//	Copy over the Geometry Draw Type.
	geometryDrawType = newGeometryDrawType;

	//	Copy over the Geometry Indices.
	geometryIndices = newGeometryIndices;

	//	Copy over the Geometry Vertices.
	geometryVertices = newGeometryVertices;

	//	Copy over the Geometry Texture Data.
	geometryTextureData = newGeometryTextureData;
}

//	
GeometryData::GeometryData(const GLenum & newGeometryDrawType, const std::vector<int>& newGeometryIndices, const std::vector<Vertex>& newGeometryVertices, const std::vector<VertexNormalData> & newGeometryNormalData, const std::vector<VertexTextureData> & newGeometryTextureData)
{
	//	
	hasGeometryVertexData = 1;
	hasGeometryVertexTextureData = 1;
	hasGeometryVertexTangentBitangentData = 0;

	//	Copy over the Geometry Draw Type.
	geometryDrawType = newGeometryDrawType;

	//	Copy over the Geometry Indices.
	geometryIndices = newGeometryIndices;

	//	Copy over the Geometry Vertices.
	geometryVertices = newGeometryVertices;

	//	Copy over the Geometry Normal Data.
	geometryNormalData = newGeometryNormalData;

	//	Copy over the Geometry Texture Data.
	geometryTextureData = newGeometryTextureData;

}

GeometryData::GeometryData(const unsigned int & newGeometryDescription, const GLenum & newGeometryDrawType, const std::vector<int>& newGeometryIndices, const std::vector<Vertex>& newGeometryVertices, const std::vector<VertexNormalData>& newGeometryNormalData, const std::vector<VertexTextureData>& newGeometryTextureData)
{


	//	Copy over the Geometry Draw Type.
	geometryDrawType = newGeometryDrawType;

	//	Copy over the Geometry Indices.
	geometryIndices = newGeometryIndices;

	//	Copy over the Geometry Vertices.
	geometryVertices = newGeometryVertices;

	//	Copy over the Geometry Normal Data.
	geometryNormalData = newGeometryNormalData;

	//	Copy over the Geometry Texture Data.
	geometryTextureData = newGeometryTextureData;

}

//	Default GeometryData Destructor.
GeometryData::~GeometryData()
{
	
}

//	Return the GLenum type.
GLenum GeometryData::getGeometryDrawType() const
{
	return geometryDrawType;
}

//	Return the Geometry Indices.
const std::vector<int> & GeometryData::viewGeometryIndices() const
{
	return geometryIndices;
}

//	Return the Geometry Vertices.
const std::vector<Vertex> & GeometryData::viewGeometryVertices() const
{
	return geometryVertices;
}

//	View the associated Geometry Normal Data.
const std::vector<VertexNormalData>& GeometryData::viewGeometryNormalData() const
{
	return geometryNormalData;
}

//	View the associated Geometry Texture Data.
const std::vector<VertexTextureData>& GeometryData::viewGeometryTextureData() const
{
	return geometryTextureData;
}

//	Return the Geometry Vertex Data.
unsigned int GeometryData::getHasVertexData() const
{
	return hasGeometryVertexData;
}

//	Return Has Vertex Texture Data.
unsigned int GeometryData::getHasVertexTextureData() const
{
	return hasGeometryVertexTextureData;
}

//	Return the Vertex Tangent Bitangent.
unsigned int GeometryData::getHasVertexTangentBitangentData() const
{
	return hasGeometryVertexTangentBitangentData;
}