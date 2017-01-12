#include "RenderableManager.h"
#include "../Renderable/Renderable.h"
#include "../RenderableTypeBatch/RenderableTypeBatch.h"
#include "../RendererResourceManagers/RendererGeometryManager/RendererGeometryManager.h"


//	Default RenderableManager Constructor.
RenderableManager::RenderableManager()
{
	//	The Default Shader Type.
	defaultShaderType = "#NO_SHADER_TYPE";

	//	The Default Geometry Type.
	defaultGeometryType = "#NO_GEOMETRY_TYPE";
	
	//	The Default Material Type.
	defaultMaterialType = "#NO_MATERIAL_TYPE";
}

//	Default RenderableManager Destructor.
RenderableManager::~RenderableManager()
{

}

//	Create a Renderable and return the RenderableID.
long int RenderableManager::createRenderable()
{
	//	Check if we have Inactive Renderables.
	if (inactiveRenderables.size() > 0)
	{
		//	Get the Renderable ID.
		long int newRenderableID = inactiveRenderables[inactiveRenderables.size() - 1];
		
		//	Remove it from the list of inactive renderables.
		inactiveRenderables.pop_back();

		//	Add it to the list of Renderables.
		activeRenderables.push_back(newRenderableID);
	
		//	Create the new Renderable.
		std::shared_ptr<Renderable> newRenderable = std::make_shared<Renderable>(newRenderableID);
		newRenderable->setShaderType(defaultShaderType);
		newRenderable->setGeometryType(defaultGeometryType);
		newRenderable->setMaterialType(defaultMaterialType);

		//	Create the New Renderrable Meta Data.
		std::shared_ptr<RenderableMetaData> newRenderableMetaData = std::make_shared<RenderableMetaData>(defaultShaderType, defaultGeometryType, defaultMaterialType);
		newRenderableMetaData->renderable = newRenderable;

		//	Insert it into the map of Renderable IDs to Renderable Meta Datas.
		mapRenderableIDToRenderableMetaData[newRenderableID] = newRenderableMetaData;

		//	Add the Renderable Meta Data to the appropriate location.
		addRenderableMetaData(newRenderableMetaData);

		//	Return the RenderableID;
		return newRenderableID;
	}
	else
	{
		//	Get the Renderable ID.
		long int newRenderableID = activeRenderables.size();

		//	Add it to the list of Renderables.
		activeRenderables.push_back(newRenderableID);

		//	Create the new Renderable.
		std::shared_ptr<Renderable> newRenderable = std::make_shared<Renderable>(newRenderableID);
		newRenderable->setShaderType(defaultShaderType);
		newRenderable->setGeometryType(defaultGeometryType);
		newRenderable->setMaterialType(defaultMaterialType);

		//	Create the New Renderrable Meta Data.
		std::shared_ptr<RenderableMetaData> newRenderableMetaData = std::make_shared<RenderableMetaData>(defaultShaderType, defaultGeometryType, defaultMaterialType);
		newRenderableMetaData->renderable = newRenderable;

		//	Insert it into the map of Renderable IDs to Renderable Meta Datas.
		mapRenderableIDToRenderableMetaData[newRenderableID] = newRenderableMetaData;

		//	Add the Renderable Meta Data to the appropriate location.
		addRenderableMetaData(newRenderableMetaData);

		//	Return the RenderableID;
		return newRenderableID;
	}
}

//	Return the const Renderable associated with the specified RenderableID.
std::shared_ptr<const Renderable> RenderableManager::viewRenderable(const long int & currentRenderableID) const
{
	auto renderableIndex = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	if (renderableIndex != mapRenderableIDToRenderableMetaData.end())
	{
		return renderableIndex->second->renderable;
	}
	else
	{
		return NULL;
	}
}

//	Return the Renderable associated with the RenderableID.
std::shared_ptr<Renderable> RenderableManager::getRenderable(const long int & currentRenderableID)
{
	std::shared_ptr<RenderableMetaData> renderableMetaData = getRenderableMetaData(currentRenderableID);

	if (renderableMetaData != NULL)
	{
		return renderableMetaData->renderable;
	}
	else
	{
		return NULL;
	}
}

//	Return the Renderable associated with the RenderableID.
std::shared_ptr<RenderableMetaData> RenderableManager::getRenderableMetaData(const long int & currentRenderableID)
{
	auto renderableIndex = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	if (renderableIndex != mapRenderableIDToRenderableMetaData.end())
	{
		return renderableIndex->second;
	}
	else
	{
		return NULL;
	}
}

//	Return the Map of the RenderableID to the RenderableMetaData
const std::map<long int, std::shared_ptr<RenderableMetaData>>& RenderableManager::getMapOfRenderableIDToRenderableMetaData() const
{
	return mapRenderableIDToRenderableMetaData;
}

//	Return the Map of the RenderableType to the RenderableTypeBatch.
const std::map<RenderableType, std::shared_ptr<RenderableTypeBatch>>& RenderableManager::getRenderableTypeBatches() const
{
	return mapRenderableTypeToRenderableTypeBatches;
}

//	Return the Renderable Type Batch Meta Datas.
const std::set<RenderableTypeBatchMetaData>& RenderableManager::getRenderableTypeBatchMetaDatas() const
{
	return renderableTypeBatchMetaDatas;
}

//	Update the Shading Type associated with the specified Renderable ID.
void RenderableManager::updateShadingType(const long int & currentRenderableID, const std::string & newShadingType)
{
	//	Find the Renderable Entry in the Map.
	auto renderableEntry = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	removeRenderableMetaData(renderableEntry->second);

	renderableEntry->second->renderableType.shaderType = newShadingType;

	renderableEntry->second->renderable->setShaderType(newShadingType);

	addRenderableMetaData(renderableEntry->second);
}

//	Update the Geometry Type associated with the specified Renderable ID.
void RenderableManager::updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType)
{
	//	Find the Renderable Entry in the Map.
	auto renderableEntry = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	removeRenderableMetaData(renderableEntry->second);

	renderableEntry->second->renderableType.geometryType = newGeometryType;

	renderableEntry->second->renderable->setGeometryType(newGeometryType);

	addRenderableMetaData(renderableEntry->second);
}

//	Update the Material Type associated with the specified Renderable ID.
void RenderableManager::updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType)
{
	//	Find the Renderable Entry in the Map.
	auto renderableEntry = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	removeRenderableMetaData(renderableEntry->second);

	renderableEntry->second->renderableType.materialType = newMaterialType;

	renderableEntry->second->renderable->setMaterialType(newMaterialType);

	addRenderableMetaData(renderableEntry->second);
}

//	Update the Transform Matrix associated with the specified Renderable ID.
void RenderableManager::updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix)
{
	//	
	auto renderableEntry = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	//	
	if (renderableEntry != mapRenderableIDToRenderableMetaData.end())
	{
		renderableEntry->second->renderableTypeBatch.lock()->updateTransformMatrix(renderableEntry->second, newTransformMatrix);
	}
}

//	Remove the Renderable, specified by RenderableID.
void RenderableManager::removeRenderable(const long int & deadRenderable)
{
	//	Find the Renderable in the map of the RenderableID to the Renderable Meta Data.
	auto renderableEntry = mapRenderableIDToRenderableMetaData.find(deadRenderable);

	//	Check if it exists.
	if (renderableEntry != mapRenderableIDToRenderableMetaData.end())
	{
		//	Get the Renderable Meta Data.
		std::shared_ptr<RenderableMetaData> renderableMetaData = renderableEntry->second;

		removeRenderableMetaData(renderableMetaData);

		mapRenderableIDToRenderableMetaData.erase(renderableEntry);

		for (int i = 0; i < activeRenderables.size(); i++)
		{
			if (activeRenderables[i] == deadRenderable)
			{
				activeRenderables[i] = activeRenderables[activeRenderables.size() - 1];
				activeRenderables.pop_back();
			}
		}

		inactiveRenderables.push_back(deadRenderable);
	}
}

//	Add the Geometry Type.
void RenderableManager::addGeometryType(std::shared_ptr<RendererGeometryData> newGeometryType)
{
	//	Add the new Geometry Type to the list of Geometry Types.
	geometryTypes.insert(newGeometryType->geometryType);
	
	//	Create the new Geometry Type Meta.
	std::shared_ptr<GeometryTypeMetaData> newGeometryTypeMetaData = std::make_shared<GeometryTypeMetaData>(newGeometryType->geometryType);
	newGeometryTypeMetaData->rendererGeometryData = newGeometryType;

	//	Add it to the VAO Backend.
	vaoStorage.addGeometryType(newGeometryTypeMetaData);

	//	Insert the Geometry Type Meta Data.
	mapGeometryTypeToGeometryTypeMetaData[newGeometryType->geometryType] = newGeometryTypeMetaData;

	//	Update the Batches.
	updateRenderableTypeBatchesWithGeometryType(newGeometryType->geometryType, true);
}

//	Update the Geometry Type.
void RenderableManager::updateGeometryType(std::shared_ptr<RendererGeometryData> updatedGeometryData)
{

}

//	Remove the Geometry Type.
void RenderableManager::removeGeometryType(std::shared_ptr<RendererGeometryData> deadGeometryType)
{
	//	Get the Geometry Type.
	std::shared_ptr<GeometryTypeMetaData> newGeometryTypeMetaData = mapGeometryTypeToGeometryTypeMetaData[deadGeometryType->geometryType];
	
	//	Delete it from VAO Storage.
	vaoStorage.deleteGeometryType(newGeometryTypeMetaData);
	
	//	Delete it from the list of Geometry Types.
	geometryTypes.erase(deadGeometryType->geometryType);
	
	//	Delete it from the Map.
	mapGeometryTypeToGeometryTypeMetaData.erase(deadGeometryType->geometryType);

	//	Update the Batches.
	updateRenderableTypeBatchesWithGeometryType(deadGeometryType->geometryType, false);
}

//	Add the Shader Type.
void RenderableManager::addShaderType(std::string newShaderType)
{
	shaderTypes.insert(newShaderType);
	updateRenderableTypeBatchesWithShaderType(newShaderType, true);
}

//	Remove the Shader Type.
void RenderableManager::removeShaderType(std::string deadShaderType)
{
	shaderTypes.erase(deadShaderType);
	updateRenderableTypeBatchesWithShaderType(deadShaderType, false);
}

//	Add the Material Type.
void RenderableManager::addMaterialType(std::string newMaterialType)
{
	materialTypes.insert(newMaterialType);
	updateRenderableTypeBatchesWithMaterialType(newMaterialType, true);
}

//	Remove the Material Type.
void RenderableManager::removeMaterialType(std::string deadMaterialType)
{
	materialTypes.erase(deadMaterialType);
	updateRenderableTypeBatchesWithMaterialType(deadMaterialType, false);
}

//	Add Renderable Meta Data.
void RenderableManager::addRenderableMetaData(std::shared_ptr<RenderableMetaData> newRenderableMetaData)
{
	std::shared_ptr<RenderableTypeBatch> renderableTypeBatch = getRenderableTypeBatch(newRenderableMetaData->renderableType);
	renderableTypeBatch->addRenderable(newRenderableMetaData);
	newRenderableMetaData->renderableTypeBatch = renderableTypeBatch;
}

//	Remove Renderable Meta Data.
void RenderableManager::removeRenderableMetaData(std::shared_ptr<RenderableMetaData> deadRenderableMetaData)
{	
	std::shared_ptr<RenderableTypeBatch> renderableTypeBatch = getRenderableTypeBatch(deadRenderableMetaData->renderableType);
	renderableTypeBatch->removeRenderable(deadRenderableMetaData);
	deadRenderableMetaData->renderableTypeBatch = std::weak_ptr<RenderableTypeBatch>();
}

//	Update the Renderable Type Batches that have the specified Shader Type, so that they hold their proper place in the list.
void RenderableManager::updateRenderableTypeBatchesWithShaderType(const std::string & shaderType, bool available)
{
	//	
	std::set<RenderableTypeBatchMetaData> newRenderableTypeBatchMetaDatas;
	
	//	Iterate over all the Renderable Type Batches.
	for (auto renderableTypeBatchEntry = renderableTypeBatchMetaDatas.begin(); renderableTypeBatchEntry != renderableTypeBatchMetaDatas.end(); renderableTypeBatchEntry++)
	{
		RenderableTypeBatchMetaData newRenderableTypeBatchMetaData = RenderableTypeBatchMetaData(*renderableTypeBatchEntry);

		//	Check for the availability of the Shader, Geometry, and Material Types.
		bool availableShaderType = isAvailableShaderType(newRenderableTypeBatchMetaData.renderableType.shaderType);
		bool availableGeometryType = isAvailableGeometryType(newRenderableTypeBatchMetaData.renderableType.geometryType);
		bool availableMaterialType = isAvailableMaterialType(newRenderableTypeBatchMetaData.renderableType.materialType);

		//	Available Shader Type.
		if (availableShaderType)
			newRenderableTypeBatchMetaData.shaderTypeMetaData = std::make_shared<ShaderTypeMetaData>(newRenderableTypeBatchMetaData.renderableType.shaderType);
		else
			newRenderableTypeBatchMetaData.shaderTypeMetaData = NULL;

		//	Available Geometry Type.
		if (availableGeometryType)
			newRenderableTypeBatchMetaData.geometryTypeMetaData = getGeometryTypeMetaData(newRenderableTypeBatchMetaData.renderableType.geometryType);
		else
			newRenderableTypeBatchMetaData.geometryTypeMetaData = NULL;

		//	Available Material Type.
		if (availableMaterialType)
			newRenderableTypeBatchMetaData.materialTypeMetaData = std::make_shared<MaterialTypeMetaData>(newRenderableTypeBatchMetaData.renderableType.materialType);
		else
			newRenderableTypeBatchMetaData.materialTypeMetaData = NULL;

		//	Update the Renderable Type Batch.
		newRenderableTypeBatchMetaData.renderableTypeBatch->setIsValidRenderableType(availableShaderType && availableGeometryType && availableMaterialType);

		//	Insert it into the new list.
		newRenderableTypeBatchMetaDatas.insert(newRenderableTypeBatchMetaData);
	}
	

	//	Swap the old list and the new one.
	std::swap(newRenderableTypeBatchMetaDatas, renderableTypeBatchMetaDatas);

}

//	Update the Renderable Type Batches with the Geometry Type, so that they hold their proper place in the list.
void RenderableManager::updateRenderableTypeBatchesWithGeometryType(const std::string & geometryType, bool available)
{
	//	
	std::set<RenderableTypeBatchMetaData> newRenderableTypeBatchMetaDatas;

	//	Iterate over all the Renderable Type Batches.
	for (auto renderableTypeBatchEntry = renderableTypeBatchMetaDatas.begin(); renderableTypeBatchEntry != renderableTypeBatchMetaDatas.end(); renderableTypeBatchEntry++)
	{
		RenderableTypeBatchMetaData newRenderableTypeBatchMetaData = RenderableTypeBatchMetaData(*renderableTypeBatchEntry);

		bool availableShaderType = isAvailableShaderType(newRenderableTypeBatchMetaData.renderableType.shaderType);
		bool availableGeometryType = isAvailableGeometryType(newRenderableTypeBatchMetaData.renderableType.geometryType);
		bool availableMaterialType = isAvailableMaterialType(newRenderableTypeBatchMetaData.renderableType.materialType);

		//	Available Shader Type.
		if (availableShaderType)
			newRenderableTypeBatchMetaData.shaderTypeMetaData = std::make_shared<ShaderTypeMetaData>(newRenderableTypeBatchMetaData.renderableType.shaderType);
		else
			newRenderableTypeBatchMetaData.shaderTypeMetaData = NULL;

		//	Available Geometry Type.
		if (availableGeometryType)
			newRenderableTypeBatchMetaData.geometryTypeMetaData = getGeometryTypeMetaData(newRenderableTypeBatchMetaData.renderableType.geometryType);
		else
			newRenderableTypeBatchMetaData.geometryTypeMetaData = NULL;

		//	Available Material Type.
		if (availableMaterialType)
			newRenderableTypeBatchMetaData.materialTypeMetaData = std::make_shared<MaterialTypeMetaData>(newRenderableTypeBatchMetaData.renderableType.materialType);
		else
			newRenderableTypeBatchMetaData.materialTypeMetaData = NULL;

		//	Update the Renderable Type Batch.
		newRenderableTypeBatchMetaData.renderableTypeBatch->setIsValidRenderableType(availableShaderType && availableGeometryType && availableMaterialType);

		//	Insert it into the new list.
		newRenderableTypeBatchMetaDatas.insert(newRenderableTypeBatchMetaData);
	}


	//	Swap the old list and the new one.
	std::swap(newRenderableTypeBatchMetaDatas, renderableTypeBatchMetaDatas);
}

//	Update the Renderable Type Batches with the Material Type, so that they hold their proper place in the list.
void RenderableManager::updateRenderableTypeBatchesWithMaterialType(const std::string & materialType, bool available)
{
	//	
	std::set<RenderableTypeBatchMetaData> newRenderableTypeBatchMetaDatas;

	//	Iterate over all the Renderable Type Batches.
	for (auto renderableTypeBatchEntry = renderableTypeBatchMetaDatas.begin(); renderableTypeBatchEntry != renderableTypeBatchMetaDatas.end(); renderableTypeBatchEntry++)
	{
		RenderableTypeBatchMetaData newRenderableTypeBatchMetaData = RenderableTypeBatchMetaData(*renderableTypeBatchEntry);

		bool availableShaderType = isAvailableShaderType(newRenderableTypeBatchMetaData.renderableType.shaderType);
		bool availableGeometryType = isAvailableGeometryType(newRenderableTypeBatchMetaData.renderableType.geometryType);
		bool availableMaterialType = isAvailableMaterialType(newRenderableTypeBatchMetaData.renderableType.materialType);

		//	Available Shader Type.
		if (availableShaderType)
			newRenderableTypeBatchMetaData.shaderTypeMetaData = std::make_shared<ShaderTypeMetaData>(newRenderableTypeBatchMetaData.renderableType.shaderType);
		else
			newRenderableTypeBatchMetaData.shaderTypeMetaData = NULL;

		//	Available Geometry Type.
		if (availableGeometryType)
			newRenderableTypeBatchMetaData.geometryTypeMetaData = getGeometryTypeMetaData(newRenderableTypeBatchMetaData.renderableType.geometryType);
		else
			newRenderableTypeBatchMetaData.geometryTypeMetaData = NULL;

		//	Available Material Type.
		if (availableMaterialType)
			newRenderableTypeBatchMetaData.materialTypeMetaData = std::make_shared<MaterialTypeMetaData>(newRenderableTypeBatchMetaData.renderableType.materialType);
		else
			newRenderableTypeBatchMetaData.materialTypeMetaData = NULL;

		//	Update the Renderable Type Batch.
		newRenderableTypeBatchMetaData.renderableTypeBatch->setIsValidRenderableType(availableShaderType && availableGeometryType && availableMaterialType);

		//	Insert it into the new list.
		newRenderableTypeBatchMetaDatas.insert(newRenderableTypeBatchMetaData);
	}


	//	Swap the old list and the new one.
	std::swap(newRenderableTypeBatchMetaDatas, renderableTypeBatchMetaDatas);
}

//	Get the Renderable Type Batch for the Renderable Type.
std::shared_ptr<RenderableTypeBatch> RenderableManager::getRenderableTypeBatch(const RenderableType & renderableType)
{
	//	Check if the appropriate Renderable Type exists.
	auto renderableTypeBatch = mapRenderableTypeToRenderableTypeBatches.find(renderableType);

	//	
	if (renderableTypeBatch != mapRenderableTypeToRenderableTypeBatches.end())
	{
		return renderableTypeBatch->second;
	}
	else
	{
		//	Check for the availability of the Shader, Geometry, and Material Types.
		bool availableShaderType = isAvailableShaderType(renderableType.shaderType);
		bool availableGeometryType = isAvailableGeometryType(renderableType.geometryType);
		bool availableMaterialType = isAvailableMaterialType(renderableType.materialType);

		RenderableTypeBatchMetaData newRenderableTypeBatchMetaData(renderableType);

		//	Available Shader Type.
		if (availableShaderType)
			newRenderableTypeBatchMetaData.shaderTypeMetaData = std::make_shared<ShaderTypeMetaData>(renderableType.shaderType);
		else
			newRenderableTypeBatchMetaData.shaderTypeMetaData = NULL;

		//	Available Geometry Type.
		if (availableGeometryType)
			newRenderableTypeBatchMetaData.geometryTypeMetaData = getGeometryTypeMetaData(renderableType.geometryType);
		else
			newRenderableTypeBatchMetaData.geometryTypeMetaData = NULL;

		//	Available Material Type.
		if (availableMaterialType)
			newRenderableTypeBatchMetaData.materialTypeMetaData = std::make_shared<MaterialTypeMetaData>(renderableType.materialType);
		else
			newRenderableTypeBatchMetaData.materialTypeMetaData = NULL;


		//	Create the new Renderable Type Batch.
		std::shared_ptr<RenderableTypeBatch> newRenderableTypeBatch = std::make_shared<RenderableTypeBatch>(renderableType);
	
		//	Set whether this is a Valid Renderable Type.
		newRenderableTypeBatch->setIsValidRenderableType(availableShaderType && availableGeometryType && availableMaterialType);

		//	Associate the Renderable Type Batch 
		newRenderableTypeBatchMetaData.renderableTypeBatch = newRenderableTypeBatch;

		//	Insert the new Renderable Type Batch.
		mapRenderableTypeToRenderableTypeBatches[renderableType] = newRenderableTypeBatch;

		//	Inset the Renderable Type Meta Data.
		renderableTypeBatchMetaDatas.insert(newRenderableTypeBatchMetaData);

		//	Return the Renderable Type Batch.
		return newRenderableTypeBatch;
	}
}

//	Return the Geometry Type Meta Data.
std::shared_ptr<GeometryTypeMetaData> RenderableManager::getGeometryTypeMetaData(const std::string & givenGeometryType)
{
	auto geometryTypeMetaData = mapGeometryTypeToGeometryTypeMetaData.find(givenGeometryType);

	if (geometryTypeMetaData != mapGeometryTypeToGeometryTypeMetaData.end())
	{
		return geometryTypeMetaData->second;
	}
	else
	{
		return NULL;
	}
}

//	Check if the Shader Type is an Available Shader Type.
bool RenderableManager::isAvailableShaderType(const std::string & givenShaderType)
{
	auto shaderTypeEntry = shaderTypes.find(givenShaderType);

	if (shaderTypeEntry != shaderTypes.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//	Check if the Geometry Type is an Available Geometry Type.
bool RenderableManager::isAvailableGeometryType(const std::string & givenGeometryType)
{
	auto geometryTypeEntry = geometryTypes.find(givenGeometryType);

	if (geometryTypeEntry != geometryTypes.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//	Check if the Material Type is an Available Material Type.
bool RenderableManager::isAvailableMaterialType(const std::string & givenMaterialType)
{
	auto materialTypeEntry = materialTypes.find(givenMaterialType);

	if (materialTypeEntry != materialTypes.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}


