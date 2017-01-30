#include "RendererMaterialManager.h"
#include "../Resources/ResourceData/MaterialData/MaterialData.h"

//	Default RendererMaterialManager Constructor.
RendererMaterialManager::RendererMaterialManager()
{

}


//	Default RendererMaterialManager Destructor.
RendererMaterialManager::~RendererMaterialManager()
{

}

//	Add a new Material from provided MaterialData and the Material Name.
void RendererMaterialManager::addMaterial(const std::string & newMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData)
{
	//	Find the Material to see if the Material exists.
	auto materialIterator = mapNameToMaterialData.find(newMaterialName);

	//	Check if the Material Already Exists.
	if (materialIterator != mapNameToMaterialData.end())
	{
		//	TO DO
		//	Throw Already Exists Error.
	}
	else
	{
		//	Create the New Material Values and Material Albedo Maps.
		std::shared_ptr<RendererMaterialData> newRendererMaterialData = std::make_shared<RendererMaterialData>();
		
		//	Copy over the Diffuse Albedo and the Metallic, Roughness, Fresnel and Opactiy.
		newRendererMaterialData->diffuseAlbedo = newMaterialData->diffuseAlbedo;
		newRendererMaterialData->specularAlbedo = newMaterialData->specularAlbedo;
		newRendererMaterialData->emissiveColor = newMaterialData->emissiveColor;
		newRendererMaterialData->metallicRoughnessFresnelOpacity = newMaterialData->metallicRoughnessFresnelOpacity;

		//	Copy over the Diffuse and Specular Albedo Maps.
		newRendererMaterialData->diffuseAlbedoTexture = newMaterialData->diffuseAlbedoTexture;
		newRendererMaterialData->specularAlbedoTexture = newMaterialData->specularAlbedoTexture;

		//	Copy over the MRFO, Normal and Occlusion Maps.
		newRendererMaterialData->MRFOTexture = newMaterialData->MRFOTexture;
		newRendererMaterialData->normalTexture = newMaterialData->normalTexture;
		newRendererMaterialData->occlusionTexture = newMaterialData->occlusionTexture;
	
		//	Associated the Material Name with the new Material Data.
		mapNameToMaterialData[newMaterialName] = newRendererMaterialData;
	}
}

//	Update the Material of the Material Name and the specified Material Data.
void RendererMaterialManager::updateMaterial(const std::string & requestedMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData)
{
	//	Find the Material to see if the Material exists.
	auto materialIterator = mapNameToMaterialData.find(requestedMaterialName);

	//	Check if the Material Already Exists.
	if (materialIterator != mapNameToMaterialData.end())
	{
		//	Copy over the Diffuse Albedo and the Metallic, Roughness, Fresnel and Opactiy.
		mapNameToMaterialData[requestedMaterialName]->diffuseAlbedo = newMaterialData->diffuseAlbedo;
		mapNameToMaterialData[requestedMaterialName]->specularAlbedo = newMaterialData->specularAlbedo;
		mapNameToMaterialData[requestedMaterialName]->emissiveColor = newMaterialData->emissiveColor;
		mapNameToMaterialData[requestedMaterialName]->metallicRoughnessFresnelOpacity = newMaterialData->metallicRoughnessFresnelOpacity;

		//	Copy over the Diffuse and Specular Albedo Maps.
		mapNameToMaterialData[requestedMaterialName]->diffuseAlbedoTexture = newMaterialData->diffuseAlbedoTexture;
		mapNameToMaterialData[requestedMaterialName]->specularAlbedoTexture = newMaterialData->specularAlbedoTexture;

		//	Copy over the MRFO, Normal and Occlusion Maps.
		mapNameToMaterialData[requestedMaterialName]->MRFOTexture = newMaterialData->MRFOTexture;
		mapNameToMaterialData[requestedMaterialName]->normalTexture = newMaterialData->normalTexture;
		mapNameToMaterialData[requestedMaterialName]->occlusionTexture = newMaterialData->occlusionTexture;
	}
	else
	{
		//	Throw does not exist error.
	}
}

//	View the Material of the specified Name.
std::shared_ptr<const RendererMaterialData> RendererMaterialManager::viewMaterial(const std::string & requestedMaterialName) const
{
	//	Find the Material to see if the Material exists.
	auto materialIterator = mapNameToMaterialData.find(requestedMaterialName);
	
	//	Check if the Material Already Exists.
	if (materialIterator != mapNameToMaterialData.end())
	{
		//	Return the Material
		return materialIterator->second;
	}
	else
	{
		//	Throw does not exist error.
		return NULL;
	}
}

//	Delete the Material of the specified Name.
void RendererMaterialManager::deleteMaterial(const std::string & deadMaterialName)
{
	//	Find the Material to see if the Material exists.
	auto materialIterator = mapNameToMaterialData.find(deadMaterialName);

	//	Check if the Material Already Exists.
	if (materialIterator != mapNameToMaterialData.end())
	{
		//	Erase the Material.
		mapNameToMaterialData.erase(materialIterator);
	}
	else
	{
		//	Throw does not exist error.
	}
}
