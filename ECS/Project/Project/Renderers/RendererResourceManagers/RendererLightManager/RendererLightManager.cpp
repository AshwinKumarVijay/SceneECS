#include "RendererLightManager.h"

//	Default RendererLightManager Constructor
RendererLightManager::RendererLightManager()
{

}


//	Default RendererLightManager Destructor
RendererLightManager::~RendererLightManager()
{

}

//	Add a Light.
void RendererLightManager::addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	Find the Light.
	auto lightIterator = mapLightNameToLightData.find(newLightName);

	//	Check if the Light actually exists.
	if (lightIterator != mapLightNameToLightData.end())
	{
		//	Throw does not exist error.
		throw "Error! RendererLightManager: Add Light -> Light with Specified Name Already Exists!";

	}
	else
	{
		//	Create the New Light.
		std::shared_ptr<RendererLightData> newLight = std::make_shared<RendererLightData>();

		newLight->lightEnabledShadowLightType = newLightData->lightEnabledShadowLightType;
		newLight->lightColorAndLightIntensity = newLightData->lightColorAndLightIntensity;
		newLight->lightPosition = newLightData->lightPosition;
		newLight->lightConeDirection = newLightData->lightConeDirection;
		newLight->lightDistanceAttenuation = newLightData->lightDistanceAttenuation;

		mapLightNameToLightData[newLightName] = newLight;
	}
}

//	Update the Light.
void RendererLightManager::updateLight(std::string requestedLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	Find the Light.
	auto lightIterator = mapLightNameToLightData.find(requestedLightName);

	//	Check if the Light actually exists.
	if (lightIterator != mapLightNameToLightData.end())
	{
		//	Update the Light.
		lightIterator->second->lightEnabledShadowLightType = newLightData->lightEnabledShadowLightType;
		lightIterator->second->lightColorAndLightIntensity = newLightData->lightColorAndLightIntensity;
		lightIterator->second->lightPosition = newLightData->lightPosition;
		lightIterator->second->lightConeDirection = newLightData->lightConeDirection;
		lightIterator->second->lightDistanceAttenuation = newLightData->lightDistanceAttenuation;
	}
	else
	{
		//	Throw does not exist error.
		throw "Error! RendererLightManager: Update Light -> Light with Specified Name Does Not Exist!";
	}
}

//	View the Names and Lights Associated with the Data.
const std::map<std::string, std::shared_ptr<RendererLightData>>& RendererLightManager::viewMapNameToLightData()
{
	return mapLightNameToLightData;
}

//	Return a const pointer to the light.
std::shared_ptr<const RendererLightData> RendererLightManager::viewLight(std::string requestedLightName)
{
	//	Find the Light.
	auto lightIterator = mapLightNameToLightData.find(requestedLightName);

	//	Check if the Light actually exists.
	if (lightIterator != mapLightNameToLightData.end())
	{
		//	Return the Light.
		return lightIterator->second;
	}
	else
	{
		//	Throw does not exist error.
		throw "Error! RendererLightManager: View Light -> Light with Specified Name Does Not Exist!";
	}
}

//	Delete the Light specified by Name.
void RendererLightManager::deleteLight(std::string deadLightName)
{
	//	Find the Light.
	auto lightIterator = mapLightNameToLightData.find(deadLightName);

	//	Check if the Light actually exists.
	if (lightIterator != mapLightNameToLightData.end())
	{
		mapLightNameToLightData.erase(lightIterator);
	}
	else
	{
		//	Throw does not exist error.
		throw "Error! RendererLightManager: Delete Light -> Light with Specified Name Does Not Exist!";
	}
}
