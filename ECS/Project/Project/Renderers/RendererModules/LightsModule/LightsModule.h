#pragma once
#include <map>
#include <memory>
#include <array>
#include "glm\glm.hpp"

#include "../RendererModule.h"

class Renderer;
class ModuleRenderer;

class RendererShaderData;

class RenderableManager;
class Camera;

struct RendererLightData;
struct SceneQuality;


struct LightModuleMetaData
{
	//	The Color Map Associated With the Light.
	unsigned int lightColorMap = 0;

	//	The Depth Map Associated With the Light.
	unsigned int lightDepthMap = 0;
		
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


class LightsModule : public RendererModule
{

public:

	//	Default LightsModule Constructor.
	LightsModule(std::shared_ptr<Renderer> newModuleRenderer);

	//	Default LightsModule Destructor.
	virtual ~LightsModule();

	//	Render the Lights Module.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Add the Light to the Renderer, under the name.
	virtual void addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData);

	//	Update the Light, as specified by the LightData.
	virtual void updateLight(std::string currentLightName, std::shared_ptr<const RendererLightData> newLightData);

	//	Delete the Light.
	virtual void deleteLight(std::string deadLightName);

	//	Return the Light Module Meta Datas.
	virtual const std::vector<LightModuleMetaData> & viewLightModuleMetaDatas() const;

	//	Upload the Light Data to the Pipeline.
	virtual void uploadLightsData(std::shared_ptr<RendererShaderData> currentRendererShaderData) const;

private:

	//	Create the Light Textures And Framebuffers.
	virtual void createLightTexturesAndFramebuffers();

	//	Map of the Name of the Light to the Module Meta Data.
	std::map<std::string, unsigned int> mapNameToLightModuleMetaDataIndex;
	
	//	Screen Width and Screen Height being of the screen being to.
	unsigned int screenWidth, screenHeight;

	//	Size of the Shadow Map being rendered to.
	unsigned int shadowMapSize;

	//	The Maximum Number of Lights allowed in the Scene.
	unsigned int maxLightCount;
	unsigned int currentLightCount;

	//	The Array of Light Module MetaData.
	std::vector<LightModuleMetaData> lightModuleMetaDatas;
};

