#include "SceneGeometryResourceManager.h"
#include "../SceneResourceManager.h"
#include "../../../Resources/ResourceData/GeometryData/GeometryData.h"
#include "../../../ECS/ECSEvent/ECSEvent.h"
#include "../../../Events/ResourceEvent/ResourceEvent.h"

//	Default SceneGeometryResourceManager Constructor.
SceneGeometryResourceManager::SceneGeometryResourceManager(std::shared_ptr<SceneResourceManager> newSceneResourceManager)
{
	sceneResourceManager = newSceneResourceManager;
}

//	Default SceneGeometryResourceManager Destructor.
SceneGeometryResourceManager::~SceneGeometryResourceManager()
{

}

//	Load the Resource Requested.
void SceneGeometryResourceManager::processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest)
{
	std::shared_ptr<SceneGeometryResourceRequest> resourceRequest = std::dynamic_pointer_cast<SceneGeometryResourceRequest>(newResourceRequest);

	if (resourceRequest->getResourceType() != "Geometry")
	{
		if (resourceRequest->getRequestType() == "ADD")
		{
			std::shared_ptr<GeometryData> newGeometryData = std::make_shared<GeometryData>(resourceRequest->geometryDataType, resourceRequest->geometryDrawType, *resourceRequest->geometryIndices, *resourceRequest->geometryVertices, *resourceRequest->geometryNormalData, *resourceRequest->geometryTextureData);


			addGeometry(resourceRequest->geometryType, newGeometryData);
		}

		if (resourceRequest->getRequestType() == "UPDATE")
		{
			std::shared_ptr<GeometryData> updatedGeometryData = std::make_shared<GeometryData>(resourceRequest->geometryDataType, resourceRequest->geometryDrawType, *resourceRequest->geometryIndices, *resourceRequest->geometryVertices, *resourceRequest->geometryNormalData, *resourceRequest->geometryTextureData);

			
			updateGeometry(resourceRequest->geometryType, updatedGeometryData);
		}

		if (resourceRequest->getRequestType() == "DELETE")
		{
			deleteGeometry(resourceRequest->geometryType);
		}
	}

}

//	Add the Geometry Data under the specified name.
void SceneGeometryResourceManager::addGeometry(std::string newGeometryName, std::shared_ptr<GeometryData> newGeometryData)
{
	auto geometryi = mapNameToGeometryData.find(newGeometryName);

	if (geometryi != mapNameToGeometryData.end())
	{
		//	Throw Geometry already present error.
		throw "Error! Scene Geometry Resource Manager : Add Geometry - Geometry with the specified Name Already Exists!";
	}
	else
	{
		//	Insert the GeometryData, under the appropriate name.
		mapNameToGeometryData.insert(std::make_pair(newGeometryName, newGeometryData));
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::GEOMETRY_RESOURCE, ResourceEventType::RESOURCE_ADDED, "GEOMETRY_MANAGER", newGeometryName, newGeometryData);
		sceneResourceManager.lock()->dispatchEventToEventQueue(newEvent);
	}
}

//	Update the Geometry Data of the the specified name. 
void SceneGeometryResourceManager::updateGeometry(std::string currentGeometryName, std::shared_ptr<GeometryData> newGeometryData)
{
	auto geometryi = mapNameToGeometryData.find(currentGeometryName);

	if (geometryi != mapNameToGeometryData.end())
	{
		geometryi->second = newGeometryData;
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::GEOMETRY_RESOURCE, ResourceEventType::RESOURCE_UPDATED, "GEOMETRY_MANAGER", currentGeometryName, newGeometryData);
		sceneResourceManager.lock()->dispatchEventToEventQueue(newEvent);
	}
	else
	{
		//	Throw did not find GeometryData error.
		throw "Error! Scene Geometry Resource Manager : Update Geometry - Geometry with the specified Name Does Not Exist!";
	}

}

//	Return a pointer to the Geometry of the specified name.
std::shared_ptr<GeometryData> SceneGeometryResourceManager::getGeometry(std::string currentGeometryName)
{
	auto geometryi = mapNameToGeometryData.find(currentGeometryName);

	if (geometryi != mapNameToGeometryData.end())
	{
		return geometryi->second;
	}
	else
	{
		//	Throw did not find GeometryData error.
		throw "Error! Scene Geometry Resource Manager : Get Geometry - Geometry with the specified Name Does Not Exist!";
		return NULL;
	}
}

//	Return a const pointer to the Geometry of the specified name.
std::shared_ptr<const GeometryData> SceneGeometryResourceManager::viewGeometry(std::string currentGeometryName) const
{
	auto geometryi = mapNameToGeometryData.find(currentGeometryName);

	if (geometryi != mapNameToGeometryData.end())
	{
		return geometryi->second;
	}
	else
	{
		//	Throw did not find GeometryData error.
		throw "Error! Scene Geometry Resource Manager : View Geometry - Geometry with the specified Name Does Not Exist!";
		return NULL;
	}
}

//	Delete the Geometry Data of the specified name.
void SceneGeometryResourceManager::deleteGeometry(std::string deadGeometryName)
{
	auto geometryi = mapNameToGeometryData.find(deadGeometryName);

	if (geometryi != mapNameToGeometryData.end())
	{
		mapNameToGeometryData.erase(deadGeometryName);
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::GEOMETRY_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, "GEOMETRY_MANAGER", deadGeometryName, nullptr);
		sceneResourceManager.lock()->dispatchEventToEventQueue(newEvent);
	}
	else
	{
		//	Throw did not find GeometryData error.
		throw "Error! Scene Geometry Resource Manager : Delete Geometry - Geometry with the specified Name Does Not Exist!";
	}
}
