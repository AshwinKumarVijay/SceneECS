#include "RendererGeometryManager.h"
#include "../../../Resources/ResourceData/GeometryData/GeometryData.h"

//	Default RendererGeometryManager Constructor
RendererGeometryManager::RendererGeometryManager()
{

}

//	Defualt RendererGeometryManager Destructor
RendererGeometryManager::~RendererGeometryManager()
{

}

//	Add the Geometry.
void RendererGeometryManager::addGeometry(std::string newGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData)
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(newGeometryName);

	//	Check if the Geometry exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Throw does not exist error.
		throw "Error! RendererGeometryManager: Add Geometry -> Geometry with Specified Name Already Exists!";
	}
	else
	{
		//	Create the new Geometry.
		std::shared_ptr<RendererGeometryData> newRendererGeometryData = std::make_shared<RendererGeometryData>(*newGeometryData);

		//	Add the Geometry to the Geometry Map.
		mapNameToGeometryData[newGeometryName] = newRendererGeometryData;
	}
}

//	Update the Geometry.
void RendererGeometryManager::updateGeometry(std::string requestedGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData)
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(requestedGeometryName);

	//	Check if the Geometry exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Create the new Geometry.
		std::shared_ptr<RendererGeometryData> newRendererGeometryData = std::make_shared<RendererGeometryData>(*newGeometryData);

		//	Replace the Geometry.
		mapNameToGeometryData[requestedGeometryName] = newRendererGeometryData;
	}
	else
	{
		//	Throw does not exist error.
		throw "Error! RendererGeometryManager: Update Geometry -> Geometry with Specified Name Does Not Exist!";
	}
}

//	Return the Geometry.
std::shared_ptr<RendererGeometryData> RendererGeometryManager::getGeometry(std::string requestedGeometryName)
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(requestedGeometryName);

	//	Check if the Geometry Exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Return the Geometry.
		return geometryIterator->second;
	}
	else
	{
		//	Throw does not exist error.
		throw "Error! RendererGeometryManager: Update Geometry -> Geometry with Specified Name Does Not Exist!";

		//	Return NULL.
		return NULL;
	}
}

//	View the Geometry.
std::shared_ptr<const RendererGeometryData> RendererGeometryManager::viewGeometry(std::string requestedGeometryName) const
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(requestedGeometryName);

	//	Check if it exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Return the Geometry.
		return geometryIterator->second;
	}
	else
	{
		//	Throw does not exist error.
		throw "Error! RendererGeometryManager: Update Geometry -> Geometry with Specified Name Does Not Exist!";

		//	Return NULL.
		return NULL;
	}
}

//	Delete the Geometry.
void RendererGeometryManager::deleteGeometry(std::string deadGeometryName)
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(deadGeometryName);

	//	Check if it exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Erase the geometry.
		mapNameToGeometryData.erase(deadGeometryName);
	}
	else
	{
		//	Throw does not exist error.
		throw "Error! RendererGeometryManager: Delete Geometry -> Geometry with Specified Name Does Not Exist!";
	}
}
