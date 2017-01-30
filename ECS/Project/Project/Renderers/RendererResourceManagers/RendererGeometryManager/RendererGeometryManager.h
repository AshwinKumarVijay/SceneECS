#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>

#include "GL\glew.h"

#include "glm\glm.hpp"

#include "../Vertex/Vertex.h"

struct RendererGeometryData
{
	//	The Name of the Geometry.
	std::string geometryType;

	//	The Geometry Data Type.
	unsigned int hasGeometryVertexData = 0;
	unsigned int hasGeometryVertexTextureData = 0;
	unsigned int hasGeometryVertexTangentBitangentData = 0;

	//	The Draw Type of the Geometry.
	GLenum geometryDrawType;

	//	The array of indices.
	std::vector<int> indicesArray;

	//	The array of vertices.
	std::vector<Vertex> verticesArray;

	//	The Vertex Texture Data of this Geometry.
	std::vector<VertexTextureData> verticesTextureData;

	//	The Vertex Normal Data of this Geometry.
	std::vector<VertexNormalData> verticesNormalData;
};

class RendererGeometryManager
{

public:
	
	//	Default RendererGeometryManager Constructor.
	RendererGeometryManager();

	//	Default RendererGeometryManager Destructor.
	virtual ~RendererGeometryManager();

	//	Add a Geometry to the RendererGeometryManager, with the specified name and the specified GeometryData.
	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData);

	//	Update the Geometry of the specified name, with the specified GeometryData.
	virtual void updateGeometry(std::string requestedGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData);

	//	Return the Geometry of the specified name.
	std::shared_ptr<RendererGeometryData> getGeometry(std::string requestedGeometryName);

	//	Return the Geometry of the specified name.
	std::shared_ptr<const RendererGeometryData> viewGeometry(std::string requestedGeometryName) const;

	//	Delete the Geometry of the specified name.
	virtual void deleteGeometry(std::string deadGeometryName);


private:

	//	Map the Name to the Geometry Data.
	std::map<std::string, std::shared_ptr<RendererGeometryData>> mapNameToGeometryData;

};

