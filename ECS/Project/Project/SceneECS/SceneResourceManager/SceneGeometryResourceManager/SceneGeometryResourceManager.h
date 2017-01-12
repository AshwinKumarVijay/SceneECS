#pragma once
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"

#include "../Vertex/Vertex.h"

#include "../SceneResourceRequest/SceneResourceRequest.h"
#include "../../../Events/ResourceEvent/ResourceEvent.h"

struct SceneGeometryResourceRequest : public SceneResourceRequest
{
	//	
	std::string geometryType;

	//	The Type of the Geometry : 0 - NO VERTEX INFORMATION, 1 - VERTEX BASIC DATA, 2 - VERTEX TANGENT BITANGENT DATA, 4 - VERTEX TEXTURE COORDINATES
	unsigned int geometryDescriptionRepresentation;

	//	The type of geometry represented.
	GLenum geometryDrawType;

	//	The indices of this geometry - into the vertices.
	std::shared_ptr<std::vector<int>> geometryIndices;

	//	The Vertices of this geometry.
	std::shared_ptr<std::vector<Vertex>> geometryVertices;

	//	The Vertex Normal Data of this Geometry.
	std::shared_ptr<std::vector<VertexNormalData>> geometryNormalData;

	//	The Vertex Texture Data of this Geometry.
	std::shared_ptr<std::vector<VertexTextureData>> geometryTextureData;

};

class SceneResourceMetaData;
class SceneGeometryResource;
class SceneResourceManager;

class GeometryData;

class ECSEvent;
class ResourceEvent;

class SceneGeometryResourceManager
{

public:
	
	//	Default Scene Geometry Resource Manager Constructor.
	SceneGeometryResourceManager(std::shared_ptr<SceneResourceManager> newSceneResourceManager);

	//	Default Scene Geometry Resource Manager Destructor.
	virtual ~SceneGeometryResourceManager();

	//	Load the Resource Requested.
	virtual void processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest);

	//	Add the Geometry Data under the specified name.
	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<GeometryData> newGeometryData);

	//	Update the Geometry Data of the the specified name. 
	virtual void updateGeometry(std::string currentGeometryName, std::shared_ptr<GeometryData> newGeometryData);

	//	Return a pointer to the Geometry of the specified name.
	std::shared_ptr<GeometryData> getGeometry(std::string currentGeometryName);

	//	Return a const pointer to the Geometry of the specified name.
	std::shared_ptr<const GeometryData> viewGeometry(std::string currentGeometryName) const;

	//	Delete the Geometry Data of the specified name.
	virtual void deleteGeometry(std::string deadGeometryName);


private:
	
	//	Associated Scene Resouce Manager.
	std::weak_ptr<SceneResourceManager> sceneResourceManager;

	//	
	std::map<std::string, std::shared_ptr<GeometryData>> mapNameToGeometryData;

};

