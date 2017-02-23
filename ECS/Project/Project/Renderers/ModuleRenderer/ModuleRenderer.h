#pragma once
#include <memory>
#include <vector>

#include "../Renderer/Renderer.h"

class RenderableManager;
class RendererModule;


class GBufferModule;

class LightsModule;
class ShadowsModule;

class RTSModule;

class DPassLightingModule;
class FPassLightingModule;

class SSAOModule;

//
//class GaussianBlurModule;
//class BloomModule;
//class HDRModule;


class ModuleRenderer : public Renderer
{

public:

	//	Default ModuleRenderer Constructor.
	ModuleRenderer();

	//	Default ModuleRenderer Destructor.
	virtual ~ModuleRenderer();

	//	Initialize the ModuleRenderer.
	virtual void initializeRenderer();

	//	Create the Renderable and return the RenderableID.
	virtual long int createRenderable();

	//	Return the const Renderable.
	virtual std::shared_ptr<const Renderable> viewRenderable(const long int & renderableID) const;

	//	Update the Renderable Shader Type.
	virtual void updateShadingType(const long int & renderableID, const std::string & newShaderType);
	//	Update the Renderable Geometry Type.
	virtual void updateGeometryType(const long int & renderableID, const std::string & newGeometryName);
	//	Update the Renderable Material Type.
	virtual void updateMaterialType(const long int & renderableID, const std::string & newMaterialName);
	//	Update the Renderable Transform Matrix.
	virtual void updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix);

	//	Render.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Remove the Renderable.
	virtual void removeRenderable(const long int & renderableID);

	//	Clean Up the Renderer.
	virtual void cleanUpRenderer();

	//	Add the Material to the Renderer for use, under the Material Name.
	virtual void addMaterial(std::string newMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData);
	//	Update the Material in the Renderer, specified by the Material Name.
	virtual void updateMaterial(std::string currentMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData);
	//	Delete the Material in the Renderer.
	virtual void deleteMaterial(std::string deadMaterialName);

	//	Add the Geometry to the Renderer for use, under the Geometry Name.
	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData);
	//	Update the Geometry in the Renderer, specified by the Geometry Name.
	virtual void updateGeometry(std::string currentGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData);
	//	Delete the Geometry.
	virtual void deleteGeometry(std::string deadGeometryName);

	//	Add Shader to the Renderer.
	virtual void addShader(std::shared_ptr<RendererShaderData> newShaderData);
	//	Delete the Shader in the Renderer.
	virtual void deleteShader(std::string deadShaderName);

	//	Add the Light to the Renderer, under the name.
	virtual void addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData);
	//	Update the Light, as specified by the LightData.
	virtual void updateLight(std::string currentLightName, std::shared_ptr<const RendererLightData> newLightData);
	//	Delete the Light.
	virtual void deleteLight(std::string deadLightName);

	//	Add the Texture to the Renderer, under the name.
	virtual void addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData);
	//	Update the Texture in the Renderer, specified by name.
	virtual void updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData);
	//	Delete the Texture in the Renderer.
	virtual void deleteTexture(std::string deadTextureName);


	//	-----------------------------------------------------------------------------------------------------------------------------	//

	//	Return the RendererShaderData for the Shading Type.
	virtual std::shared_ptr<const RendererShaderData> getRendererShaderDataForRenderableShadingType(const std::string & shaderType);

	//	Return the Renderable Manager.
	std::shared_ptr<RenderableManager> getRenderableManager();

	//	Render the Renderables of the Shader Type.
	virtual void renderRenderablesOfShaderType(const std::string & shaderType, const RendererShaderData & rendererShaderData, const glm::mat4 & currentViewMatrix, const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Upload the Camera Data to the Shader Pipeline.
	virtual void uploadCameraData(const RendererShaderData & rendererShaderData, const glm::vec4 & worldCameraPosition, const glm::mat4 & perspectiveMatrix, const glm::mat4 & viewMatrix, const glm::vec4 & cameraNearFarPlaneDistance);
	//	Upload the Model Data to the Shader Pipeline.
	virtual void uploadModelData(const RendererShaderData & rendererShaderData, const glm::mat4 & viewMatrix, const glm::mat4 & modelMatrix);
	//	Upload the Material Data to the Shading Pipeline.
	virtual void uploadMaterialData(const RendererShaderData & rendererShaderData, const glm::vec4 & diffuseAlbedo, const glm::vec4 & specularAlbedo, const glm::vec4 & emissiveColor, const glm::vec4 & metallicnessRoughnessFresnelOpacity);
	//	Upload the Material Texture Data to the Shading Pipeline.
	virtual void uploadMaterialTextureData(const RendererShaderData & rendererShaderData, const std::string & diffuseAlbedoMap, const std::string & specularAlbedoMap, const std::string & MRFOMap, const std::string & NormalMap, const std::string & OcclusionMap);
	//	Upload the Ambient Light Data.
	virtual void uploadAmbientLightData(const RendererShaderData & rendererShaderData);
	//	Upload the Lights Data to the Shader Pipeline.
	virtual void uploadLightsData(std::shared_ptr<RendererShaderData> currentRendererShaderData);
	//	Upload the Single Lights Data to the Shader Pipeline.
	virtual void uploadSingleLightsData(const RendererShaderData & rendererShaderData, const int & lightNumber);
	//	Upload the Point Light Shadow Cube Map Data.
	virtual void uploadPointLightShadowCubeMapData(const RendererShaderData & rendererShaderData);

	//	Upload G Buffer Textures.
	virtual void uploadGBufferTextures(const RendererShaderData & rendererShaderData, GLuint worldSpaceVertexPositionTexture, GLuint worldSpaceVertexNormalAndDepthTexture, GLuint ambientColorTexture, GLuint diffuseAlbedoAndLitTypeTexture, GLuint specularAlbedoAndLightingTypeTexture, GLuint mrfoTexture, GLuint emissiveColorAndIntensityTexture, GLuint depthTexture);

	//	Upload the Primary Post Process Textures.
	virtual void uploadPrimaryPostProcessTextures(const RendererShaderData & rendererShaderData, GLuint postProcessTextureOneID, GLuint postProcessTextureTwoID, GLuint postProcessTextureThreeID, GLuint postProcessTextureFourID);

	//	Upload the Secondary Post Process Textures.
	virtual void uploadSecondaryPostProcessTextures(const RendererShaderData & rendererShaderData, GLuint postProcessTextureFiveID, GLuint postProcessTextureSixID, GLuint postProcessTextureSevenID, GLuint postProcessTextureEightID);

	//	Upload the Noise Textures.
	virtual void uploadNoiseTextures(const RendererShaderData & rendererShaderData);


private:

	
	//	Initialize the Module Renderer.
	virtual void initializeModuleRenderer();

	//	Initialize the Modules.
	virtual void initializeModules();

	//	Initialize the Noise Textures();
	virtual void initializeNoiseTextures(unsigned int screenWidth, unsigned int screenHeight);

	//	Render the G Buffer Module.
	virtual void renderGBufferModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Render the Lights Module.
	virtual void renderLightsModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Render the Shadows Module.
	virtual void renderShadowsModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Render the Deferred Lighting Module.
	virtual void renderDeferredLightingModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Render the Foward Lighting Module.
	virtual void renderForwardLightingModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Render the SSAO Module.
	virtual void renderSSAOModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Render the Render To Screen Module.
	virtual void renderRTSModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);


	//	Renderer Framebuffers.
	std::map<std::string, std::shared_ptr<RendererPipelineFramebuffer>> rendererPipelineFramebuffers;

	//	Renderer Textures.
	std::map<std::string, std::shared_ptr<RendererPipelineTexture>> rendererPipelineTextures;

	//	Map Name to Renderables,
	std::map<std::string, std::shared_ptr<RendererModule>> mapNameToRendererModules;

	//	The Renderalbe Manager.
	std::shared_ptr<RenderableManager> renderableManager;

	//	The Renderer Noise Textures.
	std::shared_ptr<RendererNoiseTextures> rendererNoiseTextures;

	//	G-Buffer Module.
	std::shared_ptr<GBufferModule> gBufferModule;

	//	Lights Module.
	std::shared_ptr<LightsModule> lightsModule;

	//	Shadows Module.
	std::shared_ptr<ShadowsModule> shadowsModule;

	//	SSAO Module.
	std::shared_ptr<SSAOModule> ssaoModule;

	//	Deferred Pass Lighting Module.
	std::shared_ptr<DPassLightingModule> dPassLightingModule;
	
	//	Forward Pass Lighting Module.
	std::shared_ptr<FPassLightingModule> fPassLightingModule;

	////	HDR Module.
	//std::shared_ptr<HDRModule> hdrModule;

	////	Bloom Module.
	//std::shared_ptr<BloomModule> bloomModule;

	std::shared_ptr<RTSModule> rtsModule;

	//	Noise Textures.
	unsigned int noiseTextureOne, noiseTextureTwo, noiseTextureThree, noiseTextureFour;

};

