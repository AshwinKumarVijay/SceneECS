#include "LightsModule.h"
#include "../../RendererResourceManagers/RendererLightManager/RendererLightManager.h"
#include "../../Renderer/Renderer.h"
#include "../../ModuleRenderer/ModuleRenderer.h"
#include "../../RenderableManager/RenderableManager.h"
#include "../../Renderer/SceneMetaData.h"
#include "../../RendererResourceManagers/RendererShaderManager/RendererShaderData/RendererShaderData.h"

//	Default LightsModule Constructor.
LightsModule::LightsModule(std::shared_ptr<Renderer> newRenderer) : RendererModule(newRenderer)
{
	//	Get the Module Renderer.
	std::shared_ptr<ModuleRenderer> moduleRenderer = std::dynamic_pointer_cast<ModuleRenderer>(newRenderer);

	//	Copy over the Screen Width and Screen Height Textures.
	screenWidth = moduleRenderer->getSceneQuality().screenWidth;
	screenHeight = moduleRenderer->getSceneQuality().screenHeight;

	//	Copy over the Shadow Map Textures.
	shadowMapSize = moduleRenderer->getSceneQuality().shadowSize;

	//	Copy over the Max Light Count.
	maxLightCount = 16;
	currentLightCount = 0;

	//	Create the Light Textures And Framebuffers.
	createLightTexturesAndFramebuffers();

}

//	Default LightsModule Destructor.
LightsModule::~LightsModule()
{

}

//	Render the Lights Module.
void LightsModule::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	for (int i = 0; i < lightModuleMetaDatas.size(); i++)
	{


	}
}

//	Add a Light.
void LightsModule::addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	Find the Index of the Light Module Meta Data.
	auto lightModulei = mapNameToLightModuleMetaDataIndex.find(newLightName);

	//	Check for an existing light.
	if (lightModulei != mapNameToLightModuleMetaDataIndex.end())
	{
		throw "Light Module Error: Add Light. Light with specified name already exists!";
	}
	else
	{
		if (currentLightCount >= maxLightCount)
		{
			throw "Light Module Error: Add Light. Maximum Number of Lights Exceeded!";
		}
		else
		{
			//	Add the Light Module Meta Data.
			mapNameToLightModuleMetaDataIndex[newLightName] = currentLightCount;

			lightModuleMetaDatas[currentLightCount].lightEnabledShadowLightType = newLightData->lightEnabledShadowLightType;
			lightModuleMetaDatas[currentLightCount].lightColorAndLightIntensity = newLightData->lightColorAndLightIntensity;
			lightModuleMetaDatas[currentLightCount].lightPosition = newLightData->lightPosition;
			lightModuleMetaDatas[currentLightCount].lightDistanceAttenuation = newLightData->lightDistanceAttenuation;
			lightModuleMetaDatas[currentLightCount].lightConeDirection = newLightData->lightConeDirection;
			lightModuleMetaDatas[currentLightCount].spotCosCutOffAndExponent = newLightData->spotCosCutOffAndExponent;

			currentLightCount++;
		}
	}
}

//	Update a Light.
void LightsModule::updateLight(std::string currentLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	Find the Index of the Light Module Meta Data.
	auto lightModulei = mapNameToLightModuleMetaDataIndex.find(currentLightName);

	//	Check for an existing light.
	if (lightModulei != mapNameToLightModuleMetaDataIndex.end())
	{

		//	Get the Index of the Light.
		unsigned int lightIndex = lightModulei->second;

		lightModuleMetaDatas[lightIndex].lightEnabledShadowLightType = newLightData->lightEnabledShadowLightType;
		lightModuleMetaDatas[lightIndex].lightColorAndLightIntensity = newLightData->lightColorAndLightIntensity;
		lightModuleMetaDatas[lightIndex].lightPosition = newLightData->lightPosition;
		lightModuleMetaDatas[lightIndex].lightDistanceAttenuation = newLightData->lightDistanceAttenuation;
		lightModuleMetaDatas[lightIndex].lightConeDirection = newLightData->lightConeDirection;
		lightModuleMetaDatas[lightIndex].spotCosCutOffAndExponent = newLightData->spotCosCutOffAndExponent;

	}
	else
	{
		//	Throw an Error.
		throw "Light Module Error: Update Light. Light with specified name does not exist!";
	}

}

//	Delete a Light.
void LightsModule::deleteLight(std::string deadLightName)
{

	//	Find the Index of the Light Module Meta Data.
	auto lightModulei = mapNameToLightModuleMetaDataIndex.find(deadLightName);

	//	Check if the Light exists.
	if (lightModulei != mapNameToLightModuleMetaDataIndex.end())
	{
		unsigned int lightIndex = lightModulei->second;
		lightModuleMetaDatas[lightIndex].lightEnabledShadowLightType = glm::vec4(0.0);

		mapNameToLightModuleMetaDataIndex.erase(lightModulei);
	}
	else
	{
		//	Throw an Error.
		throw "Light Module Error: Delete Light. Light with specified name does not exist!";
	}
}

//	Return the Light Module Meta Datas.
const std::vector<LightModuleMetaData>& LightsModule::viewLightModuleMetaDatas() const
{
	return lightModuleMetaDatas;
}

//	Upload the Light Data to the Pipeline.
void LightsModule::uploadLightsData(std::shared_ptr<RendererShaderData> currentRendererShaderData) const
{
	for (unsigned int i = 0; i < lightModuleMetaDatas.size(); i++)
	{

		//	
		std::string lightPrefix = "u_lights";
		std::string currentLightAttribute = "";
		GLuint currentLightAttributeLocation = -1;

		//	
		currentLightAttribute = "lightEnabledShadowLightType";
		currentLightAttributeLocation = -1;
		currentLightAttributeLocation = glGetUniformLocation(currentRendererShaderData->getShaderID(), (lightPrefix + "[" + std::to_string(i) + "]" + "." + currentLightAttribute).c_str());
		glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightModuleMetaDatas[i].lightEnabledShadowLightType));

		if (lightModuleMetaDatas[i].lightEnabledShadowLightType[0] == 1.0)
		{
			//	CurrentLight - Position
			currentLightAttribute = "lightPosition";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentRendererShaderData->getShaderID(), (lightPrefix + "[" + std::to_string(i) + "]" + "." + currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightModuleMetaDatas[i].lightPosition));

			//	CurrentLight - Color
			currentLightAttribute = "lightColorAndLightIntensity";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentRendererShaderData->getShaderID(), (lightPrefix + "[" + std::to_string(i) + "]" + "." + currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightModuleMetaDatas[i].lightColorAndLightIntensity));

			//	CurrentLight -	Attenuation
			currentLightAttribute = "lightConeDirection";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentRendererShaderData->getShaderID(), (lightPrefix + "[" + std::to_string(i) + "]" + "." + currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightModuleMetaDatas[i].lightConeDirection));

			//	CurrentLight -	spotCosCutOffAndExponent
			currentLightAttribute = "lightSpotCosCutOffAndExponent";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentRendererShaderData->getShaderID(), (lightPrefix + "[" + std::to_string(i) + "]" + "." + currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightModuleMetaDatas[i].spotCosCutOffAndExponent));

			//	Bind the appropriate Texture Unit. Upload the Light Color Map.
			glActiveTexture(GL_TEXTURE0 + (45 + (i * 2)));
			glBindTexture(GL_TEXTURE_2D, lightModuleMetaDatas[i].lightColorMap);

			currentLightAttribute = "mainLightColorMap";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentRendererShaderData->getShaderID(), (lightPrefix + "[" + std::to_string(i) + "]" + "." + currentLightAttribute).c_str());
			if (currentLightAttributeLocation != (GLfloat)-1)
			{
				glUniform1i(currentLightAttributeLocation, 45 + (i * 2));
			}

			//	Bind the appropriate Texture Unit. Upload the Light Depth Map.
			glActiveTexture(GL_TEXTURE0 + (46 + (i * 2)));
			glBindTexture(GL_TEXTURE_2D, lightModuleMetaDatas[i].lightDepthMap);

			currentLightAttribute = "mainLightDepthMap";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentRendererShaderData->getShaderID(), (lightPrefix + "[" + std::to_string(i) + "]" + "." + currentLightAttribute).c_str());
			if (currentLightAttributeLocation != (GLfloat)-1)
			{
				glUniform1i(currentLightAttributeLocation, 46 + (i * 2));
			}

		}
	}
}


//	Create the Light Textures and Framebuffers
void LightsModule::createLightTexturesAndFramebuffers()
{
	for (unsigned int i = 0; i < maxLightCount; i++)
	{

		//	Create the new Light Module Meta Data, and add it to the array.
		LightModuleMetaData newLightModuleMetaData;

		//	Generate the Color and Depth Textures.
		//	Active Texture 0.
		glActiveTexture(GL_TEXTURE0 + 0);

		//	Generate the Light Color Map.
		glGenTextures(1, &newLightModuleMetaData.lightColorMap);
		glBindTexture(GL_TEXTURE_2D, newLightModuleMetaData.lightColorMap);
		glTextureImage2DEXT(newLightModuleMetaData.lightColorMap, GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTextureParameteri(newLightModuleMetaData.lightColorMap, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(newLightModuleMetaData.lightColorMap, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);


		//	Generate the Light Depth Map.
		glGenTextures(1, &newLightModuleMetaData.lightDepthMap);
		glBindTexture(GL_TEXTURE_2D, newLightModuleMetaData.lightDepthMap);

		glTextureImage2DEXT(newLightModuleMetaData.lightDepthMap, GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glTextureParameteri(newLightModuleMetaData.lightDepthMap, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(newLightModuleMetaData.lightDepthMap, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);


		//	Add the Light Module Meta Data.
		lightModuleMetaDatas.push_back(newLightModuleMetaData);

	}
}
