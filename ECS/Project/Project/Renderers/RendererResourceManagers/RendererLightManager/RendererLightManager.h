#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "GL\glew.h"
#include "glm\glm.hpp"


//	The Renderer Light Data.
struct RendererLightData
{
	//	Light Enabled and Shadow Light Type.
	//	Point Light = 1.0, Directional Light = 2.0, Spot Light = 3.0.
	glm::vec4 lightEnabledShadowLightType = glm::vec4(0.0, 1.0, 1.0, 0.0);

	//	Light Color and Light Intensity.
	glm::vec4 lightColorAndLightIntensity = glm::vec4(1.0, 1.0, 0.0, 1.0);

	//	Light Position.
	glm::vec4 lightPosition = glm::vec4(10, 10, 10, 1.0);

	//	Light Distance Attenuation.
	glm::vec4 lightDistanceAttenuation = glm::vec4(0.0, 0.0, 0.0, 0.0);

	//	Light Cone Direction.
	glm::vec4 lightConeDirection = glm::vec4(-1.0, -1.0, -1.0, 0.0);

	//	Spot Cosine Cutoff.
	glm::vec4 spotCosCutOffAndExponent = glm::vec4();
};



class RendererLightManager
{

public:

	//	Default RendererLightManager Constructor.
	RendererLightManager();

	//	Default RendererLightManager Destructor.
	virtual ~RendererLightManager();

	//	Add a Light to the RendererLightMananger.
	virtual void addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData);

	//	View a Light in the RendererLightMananger.
	virtual std::shared_ptr<const RendererLightData> viewLight(std::string requestedLightName);

	//	Update a Light in the RendererLightManager.
	virtual void updateLight(std::string requestedLightName, std::shared_ptr<const RendererLightData> newLightData);

	//	View the Names and Lights Associated with the Data.
	virtual const std::map<std::string, std::shared_ptr<RendererLightData>> & viewMapNameToLightData();

	//	Delete a Light in the RendererLightManager.
	virtual void deleteLight(std::string deadLightName);


private:

	//	The Names of the Lights.
	std::map<std::string, std::shared_ptr<RendererLightData>> mapLightNameToLightData;
};

