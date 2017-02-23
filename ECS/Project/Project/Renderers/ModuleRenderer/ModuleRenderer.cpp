#include "ModuleRenderer.h"
#include "../RenderableManager/RenderableManager.h"
#include "../RendererModules/RendererModule.h"
#include "../RendererModules/GBufferModule/GBufferModule.h"
#include "../RendererModules/LightsModule/LightsModule.h"
#include "../RendererModules/ShadowsModule/ShadowsModule.h"
#include "../RendererModules/SSAOModule/SSAOModule.h"
#include "../RendererModules/DPassLightingModule/DPassLightingModule.h"
#include "../RendererModules/FPassLightingModule/FPassLightingModule.h"
#include "../RendererModules/RTSModule/RTSModule.h"

#include "../RendererResourceManagers/RendererShaderManager/RendererShaderData/RendererShaderData.h"
#include "../../RNGs/RNGs.h"

//	Default ModuleRenderer Constructor.
ModuleRenderer::ModuleRenderer()
{

}

//	Default ModuleRenderer Destructor.
ModuleRenderer::~ModuleRenderer()
{

}

//	Initialize the ModuleRenderer.
void ModuleRenderer::initializeRenderer()
{
	//	The Renderable Manager.
	renderableManager = std::make_shared<RenderableManager>();

	//	Initialize the Module Renderer.
	initializeModuleRenderer();

	//	Initialize the Noise Textures.
	initializeNoiseTextures(getSceneQuality().screenWidth, getSceneQuality().screenHeight);

	//	Initialize the Modules.
	initializeModules();
}


//	Create the Renderable and return the RenderableID.
long int ModuleRenderer::createRenderable()
{
	return renderableManager->createRenderable();
}

//	View the Renderable associated.
std::shared_ptr<const Renderable> ModuleRenderer::viewRenderable(const long int & renderableID) const
{
	return renderableManager->viewRenderable(renderableID);
}

//	Update the Renderable Shader Type.
void ModuleRenderer::updateShadingType(const long int & renderableID, const std::string & newShaderType)
{
	renderableManager->updateShadingType(renderableID, newShaderType);
}

//	Update the Renderable Geometry Type.
void ModuleRenderer::updateGeometryType(const long int & renderableID, const std::string & newGeometryName)
{
	renderableManager->updateGeometryType(renderableID, newGeometryName);
}

//	Update the Renderable Material Type.
void ModuleRenderer::updateMaterialType(const long int & renderableID, const std::string & newMaterialName)
{
	renderableManager->updateMaterialType(renderableID, newMaterialName);
}

//	Update the Renderable Transform Matrix.
void ModuleRenderer::updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix)
{
	renderableManager->updateTransformMatrix(renderableID, newModelMatrix);
}

//	Render the Scene.
void ModuleRenderer::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	Render the G Buffer Module.
	renderGBufferModule(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);

	//	Render the Lights Module.
	renderLightsModule(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);

	//	Render the Shadows Module.
	renderShadowsModule(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);

	//	Render the Deferred Lighting Module.
	renderDeferredLightingModule(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);

	//	Render the SSAO Module.
	renderSSAOModule(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);

	//	Render the RTS Module.
	renderRTSModule(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);

}

//	Remove the Renderable.
void ModuleRenderer::removeRenderable(const long int & renderableID)
{
	renderableManager->removeRenderable(renderableID);
}

//	Clean Up the Renderer.
void ModuleRenderer::cleanUpRenderer()
{


}

//	Add the Material to the Renderer for use, under the Material Name.
void ModuleRenderer::addMaterial(std::string newMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData)
{
	Renderer::addMaterial(newMaterialName, newMaterialData);
	renderableManager->addMaterialType(newMaterialName);
}

//	Update the Material in the Renderer, specified by the Material Name.
void ModuleRenderer::updateMaterial(std::string currentMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData)
{
	Renderer::updateMaterial(currentMaterialName, newMaterialData);
}

//	Delete the Material in the Renderer.
void ModuleRenderer::deleteMaterial(std::string deadMaterialName)
{
	renderableManager->removeMaterialType(deadMaterialName);
	Renderer::deleteMaterial(deadMaterialName);
}

//	Add the Geometry to the Renderer for use, under the Geometry Name.
void ModuleRenderer::addGeometry(std::string newGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData)
{
	Renderer::addGeometry(newGeometryName, newGeometryData);

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Adding Geometry Data Error -> " << err << std::endl;
	}

	renderableManager->addGeometryType(getGeometryManager()->getGeometry(newGeometryName));

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Adding Geometry Data Error -> " << err2 << std::endl;
	}

}

//	Update the Geometry in the Renderer, specified by the Geometry Name.
void ModuleRenderer::updateGeometry(std::string currentGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData)
{
	Renderer::updateGeometry(currentGeometryName, newGeometryData);

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Updating Geometry Data Error -> " << err << std::endl;
	}


	renderableManager->updateGeometryType(getGeometryManager()->getGeometry(currentGeometryName));

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Updating Geometry Data Error -> " << err2 << std::endl;
	}
}

//	Delete the Geometry.
void ModuleRenderer::deleteGeometry(std::string deadGeometryName)
{
	renderableManager->removeGeometryType(getGeometryManager()->getGeometry(deadGeometryName));

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Deleting Geometry Data Error -> " << err << std::endl;
	}


	Renderer::deleteGeometry(deadGeometryName);

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Deleting Geometry Data Error -> " << err2 << std::endl;
	}
}

//	Add Shader to the Renderer.
void ModuleRenderer::addShader(std::shared_ptr<RendererShaderData> newShaderData)
{
	//	Add the RendererShaderData.
	Renderer::addShader(newShaderData);

	//	
	std::string newShaderType;
	if (newShaderData->getPropertyValue("Renderable Shader Type", newShaderType))
	{
		renderableManager->addShaderType(newShaderType);
	}
}

//	Delete the Shader in the Renderer.
void ModuleRenderer::deleteShader(std::string deadShaderName)
{

	std::shared_ptr<const RendererShaderData> deadShaderData = getShaderManager()->viewShaderData(deadShaderName);

	//	
	std::string deadShaderType;
	if (deadShaderData->getPropertyValue("Rendererable Shader Type", deadShaderType))
	{
		renderableManager->removeShaderType("OPAQUE_BASIC");
	}

	Renderer::deleteShader(deadShaderName);
}

//	Add a Light.
void ModuleRenderer::addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	Add the LightData under the specified name.
	Renderer::addLight(newLightName, newLightData);

	lightsModule->addLight(newLightName, getLightManager()->viewLight(newLightName));

}

//	Update the Light.
void ModuleRenderer::updateLight(std::string currentLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	Renderer::updateLight(currentLightName, newLightData);
	
	lightsModule->updateLight(currentLightName, getLightManager()->viewLight(currentLightName));
}

//	Delete the Light.
void ModuleRenderer::deleteLight(std::string deadLightName)
{
	//	Delete the Light from the Lights.
	Renderer::deleteLight(deadLightName);

	lightsModule->deleteLight(deadLightName);
}

//	Add the Texture to the Renderer, under the name.
void ModuleRenderer::addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::addTexture(newTextureName, newTextureData);
}

//	Update the Texture in the Renderer, specified by name.
void ModuleRenderer::updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::updateTexture(currentTextureName, newTextureData);
}

//	Delete the Texture in the Renderer.
void ModuleRenderer::deleteTexture(std::string deadTextureName)
{
	Renderer::deleteTexture(deadTextureName);
}

//	Return the RendererShaderData for the Shading Type.
std::shared_ptr<const RendererShaderData> ModuleRenderer::getRendererShaderDataForRenderableShadingType(const std::string & shaderType)
{
	//	RETURN THE OPAQUE SHADER DATA. 
	if (shaderType == "OPAQUE_BASIC")
	{
		return getShaderManager()->viewShaderData("Basic Deferred G Buffer Shader");
	}
	else if (shaderType == "OPAQUE_DIFFUSE_TEXTURE")
	{
		return getShaderManager()->viewShaderData("Diffuse Texture Deferred G Buffer Shader");
	}

	return NULL;
}

//	Return the Renderable Manager.
std::shared_ptr<RenderableManager> ModuleRenderer::getRenderableManager()
{
	return renderableManager;
}

//	Render the Renderables of the Shader Type.
void ModuleRenderer::renderRenderablesOfShaderType(const std::string & shaderType, const RendererShaderData & rendererShaderData, const glm::mat4 & currentViewMatrix, const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{

	//	
	GLenum cerr1 = GL_NO_ERROR;
	while ((cerr1 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Pre-Render Renderables Error -> " << cerr1 << std::endl;
	}


	//	Get the Current Shader Program.
	GLuint currentShaderProgramID = rendererShaderData.getShaderID();


	std::string currentShaderType;
	if (rendererShaderData.getPropertyValue("Shader Type", currentShaderType))
	{
		//	Get the Required Geometry Description for the Shader Type.
		int currentShaderTypeRequirements = getShaderManager()->getGeometryVertexRequirementsForShader(currentShaderType);
	}


	//	Get the Renderable Batch Types.
	const std::set<RenderableTypeBatchMetaData> & renderableBatchTypes = renderableManager->getRenderableTypeBatchMetaDatas();

	//	
	unsigned int currentVAO = 0;
	glBindVertexArray(currentVAO);

	//	
	for (auto currentRenderableTypeBatch = renderableBatchTypes.begin(); currentRenderableTypeBatch != renderableBatchTypes.end(); currentRenderableTypeBatch++)
	{
		if (currentRenderableTypeBatch->renderableTypeBatch->getIsValidRenderableType())
		{
			if (currentRenderableTypeBatch->renderableType.shaderType == shaderType)
			{
				currentVAO = currentRenderableTypeBatch->geometryTypeMetaData->vaoMetaData.lock()->vaoID;

				if (currentVAO != 0)
				{
					glBindVertexArray(currentVAO);

					//	All of this should be replaced with a single glBindVertexArray.
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentRenderableTypeBatch->geometryTypeMetaData->EBO);

					//	Get the Current Material Data.
					std::shared_ptr<const RendererMaterialData> currentMaterialData = getMaterialManager()->viewMaterial(currentRenderableTypeBatch->renderableType.materialType);

					//	Upload the Shader Material Data.
					uploadMaterialData(rendererShaderData, currentMaterialData->diffuseAlbedo, currentMaterialData->specularAlbedo, currentMaterialData->emissiveColor, currentMaterialData->metallicRoughnessFresnelOpacity);

					//	Upload the Shader Material Texture Data.
					uploadMaterialTextureData(rendererShaderData, currentMaterialData->diffuseAlbedoTexture, currentMaterialData->specularAlbedoTexture, currentMaterialData->MRFOTexture, currentMaterialData->normalTexture, currentMaterialData->occlusionTexture);

					//	
					for (int i = 0; i < currentRenderableTypeBatch->renderableTypeBatch->getTransformMatrices().size(); i++)
					{
						//	Update the Transform Matrix.
						uploadModelData(rendererShaderData, currentViewMatrix, currentRenderableTypeBatch->renderableTypeBatch->getTransformMatrices()[i]);

						//	Draw the Elements.
						glDrawElements(currentRenderableTypeBatch->geometryTypeMetaData->rendererGeometryData->geometryDrawType, currentRenderableTypeBatch->geometryTypeMetaData->rendererGeometryData->indicesArray.size(), GL_UNSIGNED_INT, 0);
					}
				}
			}
		}
	}

	glBindVertexArray(0);

	//	
	GLenum cerr2 = GL_NO_ERROR;
	while ((cerr2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post-Render Renderables Error -> " << cerr2 << std::endl;
	}
}

//	Upload the Camera Data to the Shader Pipeline.
void ModuleRenderer::uploadCameraData(const RendererShaderData & rendererShaderData, const glm::vec4 & worldCameraPosition, const glm::mat4 & perspectiveMatrix, const glm::mat4 & viewMatrix, const glm::vec4 & cameraNearFarPlaneDistance)
{
	//	Upload the Camera Position.
	int u_worldCameraPosition = -1;
	if (rendererShaderData.getUniformLocation("u_worldCameraPosition", u_worldCameraPosition))
	{
		if (u_worldCameraPosition != -1)
		{
			glUniform4fv(u_worldCameraPosition, 1, glm::value_ptr(worldCameraPosition));
		}
	}


	//	Upload the Camera Perspective Matrix.
	int u_cameraPerspectiveMatrix = -1;
	if (rendererShaderData.getUniformLocation("u_cameraPerspectiveMatrix", u_cameraPerspectiveMatrix))
	{
		if (u_cameraPerspectiveMatrix != -1)
		{
			glUniformMatrix4fv(u_cameraPerspectiveMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
		}
	}

	//	Upload the Camera View Matrix.
	int u_cameraViewMatrix = -1;
	if (rendererShaderData.getUniformLocation("u_cameraViewMatrix", u_cameraViewMatrix))
	{
		if (u_cameraViewMatrix != -1)
		{
			glUniformMatrix4fv(u_cameraViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		}
	}

	//	Upload the Screen Spae View Matrix.
	int u_screenSpaceViewMatrix = -1;
	if (rendererShaderData.getUniformLocation("u_screenSpaceViewMatrix", u_screenSpaceViewMatrix))
	{
		if (u_screenSpaceViewMatrix != -1)
		{
			glUniformMatrix4fv(u_screenSpaceViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(viewMatrix))));
		}
	}


	//	Upload the Screen Spae View Matrix.
	int u_cameraNearFarPlaneDistance = -1;
	if (rendererShaderData.getUniformLocation("u_cameraNearFarPlaneDistance", u_cameraNearFarPlaneDistance))
	{
		if (u_cameraNearFarPlaneDistance != -1)
		{
			glUniform4fv(u_cameraNearFarPlaneDistance, 1, glm::value_ptr(cameraNearFarPlaneDistance));
		}
	}


	//	Upload the Inverse Transpose Camera View Matrix.
	int u_inverseTransposeCameraViewMatrix = -1;
	if (rendererShaderData.getUniformLocation("u_inverseTransposeCameraViewMatrix", u_inverseTransposeCameraViewMatrix))
	{
		if (u_inverseTransposeCameraViewMatrix != -1)
		{
			glUniformMatrix3fv(u_inverseTransposeCameraViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(viewMatrix))));
		}
	}

}

//	Upload the Model Data to the Shader Pipeline.
void ModuleRenderer::uploadModelData(const RendererShaderData & rendererShaderData, const glm::mat4 & viewMatrix, const glm::mat4 & modelMatrix)
{
	//	
	GLenum cerr1 = GL_NO_ERROR;
	while ((cerr1 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Pre-Model Upload Error -> " << cerr1 << std::endl;
	}

	//	Upload the Model Matrix.
	int u_modelMatrix = -1;
	if (rendererShaderData.getUniformLocation("u_modelMatrix", u_modelMatrix))
	{
		if (u_modelMatrix != -1)
		{
			glUniformMatrix4fv(u_modelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}
	}

	//	Upload the Inverse Transpose Model Matrix.
	int u_inverseTransposeModelMatrix = -1;
	if (rendererShaderData.getUniformLocation("u_inverseTransposeModelMatrix", u_inverseTransposeModelMatrix))
	{
		if (u_inverseTransposeModelMatrix != -1)
		{
			glUniformMatrix3fv(u_inverseTransposeModelMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(modelMatrix))));
		}
	}


	//	Upload the ModelView Matrix.
	int u_modelViewMatrix = -1;
	if (rendererShaderData.getUniformLocation("u_modelViewMatrix", u_modelViewMatrix))
	{
		if (u_modelViewMatrix != -1)
		{
			glUniformMatrix4fv(u_modelViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix * modelMatrix));
		}
	}



	//	Upload the Inverse Transpose Model View Matrix.
	int u_inverseTransposeModelViewMatrix = -1;
	if (rendererShaderData.getUniformLocation("u_inverseTransposeModelViewMatrix", u_inverseTransposeModelViewMatrix))
	{
		if (u_inverseTransposeModelViewMatrix != -1)
		{
			glUniformMatrix3fv(u_inverseTransposeModelViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(viewMatrix * modelMatrix))));
		}
	}

	//	
	GLenum cerr2 = GL_NO_ERROR;
	while ((cerr2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post-Model Upload Error -> " << cerr2 << std::endl;
	}
}

//	Upload the Material Data to the Shading Pipeline.
void ModuleRenderer::uploadMaterialData(const RendererShaderData & rendererShaderData, const glm::vec4 & diffuseAlbedo, const glm::vec4 & specularAlbedo, const glm::vec4 & emissiveColor, const glm::vec4 & metallicnessRoughnessFresnelOpacity)
{
	//	
	GLenum cerr1 = GL_NO_ERROR;
	while ((cerr1 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Pre-Material Upload Error -> " << cerr1 << std::endl;
	}


	//	Upload the Diffuse Albedo.
	int u_diffuseAlbedoAndLitType = -1;
	if (rendererShaderData.getUniformLocation("u_diffuseAlbedoAndLitType", u_diffuseAlbedoAndLitType))
	{
		if (u_diffuseAlbedoAndLitType != -1)
		{
			glUniform4fv(u_diffuseAlbedoAndLitType, 1, glm::value_ptr(diffuseAlbedo));
		}
	}


	//	Upload the Specular Albedo.
	int u_specularAlbedoAndLightingType = -1;
	if (rendererShaderData.getUniformLocation("u_specularAlbedoAndLightingType", u_specularAlbedoAndLightingType))
	{
		if (u_specularAlbedoAndLightingType != -1)
		{
			glUniform4fv(u_specularAlbedoAndLightingType, 1, glm::value_ptr(specularAlbedo));
		}
	}


	//	Upload the Emissive Color.
	int u_emssionColorAndIntensity = -1;
	if (rendererShaderData.getUniformLocation("u_emssionColorAndIntensity", u_emssionColorAndIntensity))
	{
		if (u_emssionColorAndIntensity != -1)
		{
			glUniform4fv(u_emssionColorAndIntensity, 1, glm::value_ptr(emissiveColor));
		}
	}

	//	Upload the Metallicness, Roughness, Fresnel and Opacity.
	int u_metallicnessRoughnessFresnelOpacity = -1;
	if (rendererShaderData.getUniformLocation("u_metallicnessRoughnessFresnelOpacity", u_metallicnessRoughnessFresnelOpacity))
	{
		if (u_metallicnessRoughnessFresnelOpacity != -1)
		{
			glUniform4fv(u_metallicnessRoughnessFresnelOpacity, 1, glm::value_ptr(metallicnessRoughnessFresnelOpacity));
		}
	}

	//	
	GLenum cerr2 = GL_NO_ERROR;
	while ((cerr2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post-Material Upload Error -> " << cerr2 << std::endl;
	}
}

//	Upload the Material Texture Data to the Shading Pipeline.
void ModuleRenderer::uploadMaterialTextureData(const RendererShaderData & rendererShaderData, const std::string & diffuseAlbedoTexture, const std::string & specularAlbedoTexture, const std::string & MRFOTexture, const std::string & normalTexture, const std::string & occlusionTexture)
{
	//	Get the Diffuse Albedo Texture.
	int u_diffuseAlbedoTexture = -1;
	if (rendererShaderData.getUniformLocation("u_diffuseAlbedoTexture", u_diffuseAlbedoTexture))
	{
		if (u_diffuseAlbedoTexture != -1 && diffuseAlbedoTexture != "")
		{
			std::shared_ptr<const RendererTextureData> currentDiffuseTexture = getTextureManager()->viewTexture(diffuseAlbedoTexture);

			glActiveTexture(GL_TEXTURE0 + 15);
			glBindTexture(GL_TEXTURE_2D, currentDiffuseTexture->textureID);
			glUniform1i(u_diffuseAlbedoTexture, 15);
			glActiveTexture(GL_TEXTURE0);
		}
	}

	//	Get the Specular Albedo Texture.
	int u_specularAlbedoTexture = -1;
	if (rendererShaderData.getUniformLocation("u_specularAlbedoTexture", u_specularAlbedoTexture))
	{
		if (u_specularAlbedoTexture != -1)
		{

		}
	}

	//	Get the MRFO Texture.
	int u_mrfoTexture = -1;
	if (rendererShaderData.getUniformLocation("u_mrfoTexture", u_mrfoTexture))
	{
		if (u_mrfoTexture != -1)
		{

		}
	}

	//	Get the Normal Texture.
	int u_normalTexture = -1;
	if (rendererShaderData.getUniformLocation("u_normalTexture", u_normalTexture))
	{
		if (u_normalTexture != -1)
		{

		}
	}

	//	Get the Occlusion Texture.
	int u_occlusionTexture = -1;
	if (rendererShaderData.getUniformLocation("u_occlusionTexture", u_occlusionTexture))
	{
		if (u_occlusionTexture != -1)
		{

		}
	}

}

//	Upload the Ambient Light Data.
void ModuleRenderer::uploadAmbientLightData(const RendererShaderData & rendererShaderData)
{
	//	Upload the Ambient Light Data.
	int ambientLightLocation = -1;
	if (rendererShaderData.getUniformLocation("u_ambientLight", ambientLightLocation))
	{
		glUniform4fv(ambientLightLocation, 1, glm::value_ptr(glm::vec4(0.025, 0.025, 0.025, 1.0)));
	}
}

//	Upload the Lights Data to the Shader Pipeline.
void ModuleRenderer::uploadLightsData(std::shared_ptr<RendererShaderData> rendererShaderData)
{
	lightsModule->uploadLightsData(rendererShaderData);
}

//	Upload the Single Lights Data to the Shader Pipeline.
void ModuleRenderer::uploadSingleLightsData(const RendererShaderData & rendererShaderData, const int & lightNumber)
{

}

//	Upload the Point Light Shadow Cube Map Data.
void ModuleRenderer::uploadPointLightShadowCubeMapData(const RendererShaderData & rendererShaderData)
{

}

//	Upload the G Buffer Textures.
void ModuleRenderer::uploadGBufferTextures(const RendererShaderData & rendererShaderData, GLuint worldSpaceVertexPositionTexture, GLuint worldSpaceVertexNormalAndDepthTexture, GLuint ambientColorTexture, GLuint diffuseAlbedoAndLitTypeTexture, GLuint specularAlbedoAndLightingTypeTexture, GLuint mrfoTexture, GLuint emissiveColorAndIntensityTexture, GLuint depthTexture)
{
	//	Upload the World Space Vertex Position Textutre.
	int g_worldSpaceVertexPosition = -1;
	if (rendererShaderData.getUniformLocation("g_worldSpaceVertexPosition", g_worldSpaceVertexPosition))
	{
		if (g_worldSpaceVertexPosition != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 20);
			glBindTexture(GL_TEXTURE_2D, worldSpaceVertexPositionTexture);
			glUniform1i(g_worldSpaceVertexPosition, 20);
			glActiveTexture(GL_TEXTURE0);
		}
	}

	//	Upload the World Space Vertex and Depth Texture.
	int g_worldSpaceVertexNormalAndDepth = -1;
	if (rendererShaderData.getUniformLocation("g_worldSpaceVertexNormalAndDepth", g_worldSpaceVertexNormalAndDepth))
	{
		if (g_worldSpaceVertexNormalAndDepth != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 21);
			glBindTexture(GL_TEXTURE_2D, worldSpaceVertexNormalAndDepthTexture);
			glUniform1i(g_worldSpaceVertexNormalAndDepth, 21);
			glActiveTexture(GL_TEXTURE0);
		}
	}


	//	Upload the Diffuse Albedo and Lit Type.
	int g_diffuseAlbedoAndLitType = -1;
	if (rendererShaderData.getUniformLocation("g_diffuseAlbedoAndLitType", g_diffuseAlbedoAndLitType))
	{
		if (g_diffuseAlbedoAndLitType != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 22);
			glBindTexture(GL_TEXTURE_2D, diffuseAlbedoAndLitTypeTexture);
			glUniform1i(g_diffuseAlbedoAndLitType, 22);
			glActiveTexture(GL_TEXTURE0);
		}
	}

	//	Upload the Specular Albedo and Lighting Type.
	int g_specularAlbedoAndLightingType = -1;
	if (rendererShaderData.getUniformLocation("g_specularAlbedoAndLightingType", g_specularAlbedoAndLightingType))
	{
		if (g_specularAlbedoAndLightingType != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 23);
			glBindTexture(GL_TEXTURE_2D, specularAlbedoAndLightingTypeTexture);
			glUniform1i(g_specularAlbedoAndLightingType, 23);
			glActiveTexture(GL_TEXTURE0);
		}
	}

	//	Upload the Metallicness, Roughness, Fresnel and Opacity.
	int g_metallicnessRoughnessFresnelOpacity = -1;
	if (rendererShaderData.getUniformLocation("g_metallicnessRoughnessFresnelOpacity", g_metallicnessRoughnessFresnelOpacity))
	{
		if (g_metallicnessRoughnessFresnelOpacity != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 24);
			glBindTexture(GL_TEXTURE_2D, mrfoTexture);
			glUniform1i(g_metallicnessRoughnessFresnelOpacity, 24);
			glActiveTexture(GL_TEXTURE0);
		}
	}


	//	Upload the Emission Color And Intensity.
	int g_emissionColorAndIntensity = -1;
	if (rendererShaderData.getUniformLocation("g_emissionColorAndIntensity", g_emissionColorAndIntensity))
	{
		if (g_emissionColorAndIntensity != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 25);
			glBindTexture(GL_TEXTURE_2D, emissiveColorAndIntensityTexture);
			glUniform1i(g_emissionColorAndIntensity, 25);
			glActiveTexture(GL_TEXTURE0);
		}
	}
}

//	Upload the Primary Post Process Textures.
void ModuleRenderer::uploadPrimaryPostProcessTextures(const RendererShaderData & rendererShaderData, GLuint postProcessTextureOneID, GLuint postProcessTextureTwoID, GLuint postProcessTextureThreeID, GLuint postProcessTextureFourID)
{
	//	Get the Uniform Location of the Post Process Input Texture One.
	int pp_inputTextureOne = -1;
	if (rendererShaderData.getUniformLocation("pp_inputTextureOne", pp_inputTextureOne))
	{
		if (pp_inputTextureOne != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 35);
			glBindTexture(GL_TEXTURE_2D, postProcessTextureOneID);
			glUniform1i(pp_inputTextureOne, 35);
			glActiveTexture(GL_TEXTURE0);
		}
	}

	//	Get the Uniform Location of the Post Process Input Texture Two.
	int pp_inputTextureTwo = -1;
	if (rendererShaderData.getUniformLocation("pp_inputTextureTwo", pp_inputTextureTwo))
	{
		if (pp_inputTextureTwo != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 36);
			glBindTexture(GL_TEXTURE_2D, postProcessTextureTwoID);
			glUniform1i(pp_inputTextureTwo, 36);
			glActiveTexture(GL_TEXTURE0);
		}
	}

	//	Get the Uniform Location of the Post Process Input Texture Three.
	int pp_inputTextureThree = -1;
	if (rendererShaderData.getUniformLocation("pp_inputTextureThree", pp_inputTextureThree))
	{
		if (pp_inputTextureThree != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 37);
			glBindTexture(GL_TEXTURE_2D, postProcessTextureThreeID);
			glUniform1i(pp_inputTextureThree, 37);
			glActiveTexture(GL_TEXTURE0);
		}
	}


	//	Get the Uniform Location of the Post Process Input Texture Four.
	int pp_inputTextureFour = -1;
	if (rendererShaderData.getUniformLocation("pp_inputTextureFour", pp_inputTextureFour))
	{
		if (pp_inputTextureFour != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 38);
			glBindTexture(GL_TEXTURE_2D, postProcessTextureFourID);
			glUniform1i(pp_inputTextureFour, 38);
			glActiveTexture(GL_TEXTURE0);
		}
	}
}

//	Upload the Secondary Post Process Textures.
void ModuleRenderer::uploadSecondaryPostProcessTextures(const RendererShaderData & rendererShaderData, GLuint postProcessTextureFiveID, GLuint postProcessTextureSixID, GLuint postProcessTextureSevenID, GLuint postProcessTextureEightID)
{
	//	Get the Uniform Location of the Post Process Input Texture Five.
	int pp_inputTextureFive = -1;
	if (rendererShaderData.getUniformLocation("pp_inputTextureFive", pp_inputTextureFive))
	{
		if (pp_inputTextureFive != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 39);
			glBindTexture(GL_TEXTURE_2D, postProcessTextureFiveID);
			glUniform1i(pp_inputTextureFive, 39);
			glActiveTexture(GL_TEXTURE0);
		}
	}


	//	Get the Uniform Location of the Post Process Input Texture Six.
	int pp_inputTextureSix = -1;
	if (rendererShaderData.getUniformLocation("pp_inputTextureSix", pp_inputTextureSix))
	{
		if (pp_inputTextureSix != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 40);
			glBindTexture(GL_TEXTURE_2D, postProcessTextureSixID);
			glUniform1i(pp_inputTextureSix, 40);
			glActiveTexture(GL_TEXTURE0);
		}
	}


	//	Get the Uniform Location of the Post Process Input Texture Seven.
	int pp_inputTextureSeven = -1;
	if (rendererShaderData.getUniformLocation("pp_inputTextureSeven", pp_inputTextureSeven))
	{
		if (pp_inputTextureSeven != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 41);
			glBindTexture(GL_TEXTURE_2D, postProcessTextureSevenID);
			glUniform1i(pp_inputTextureSeven, 41);
			glActiveTexture(GL_TEXTURE0);
		}
	}


	//	Get the Uniform Location of the Post Process Input Texture Eight.
	int pp_inputTextureEight = -1;
	if (rendererShaderData.getUniformLocation("pp_inputTextureEight", pp_inputTextureEight))
	{
		if (pp_inputTextureEight != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 42);
			glBindTexture(GL_TEXTURE_2D, postProcessTextureEightID);
			glUniform1i(pp_inputTextureEight, 42);
			glActiveTexture(GL_TEXTURE0);
		}
	}


}

//	Upload the Noise Textures.
void ModuleRenderer::uploadNoiseTextures(const RendererShaderData & rendererShaderData)
{
	int t_noiseTextureOne = -1;
	if (rendererShaderData.getUniformLocation("t_noiseTextureOne", t_noiseTextureOne))
	{
		glActiveTexture(GL_TEXTURE0 + 15);
		glBindTexture(GL_TEXTURE_2D, noiseTextureOne);
		glUniform1i(t_noiseTextureOne, 15);
		glActiveTexture(GL_TEXTURE0);
	}

	int t_noiseTextureTwo = -1;
	if (rendererShaderData.getUniformLocation("t_noiseTextureTwo", t_noiseTextureTwo))
	{
		glActiveTexture(GL_TEXTURE0 + 16);
		glBindTexture(GL_TEXTURE_2D, noiseTextureTwo);
		glUniform1i(t_noiseTextureTwo, 16);
		glActiveTexture(GL_TEXTURE0);
	}

	int t_noiseTextureThree = -1;
	if (rendererShaderData.getUniformLocation("t_noiseTextureThree", t_noiseTextureThree))
	{
		glActiveTexture(GL_TEXTURE0 + 17);
		glBindTexture(GL_TEXTURE_2D, noiseTextureThree);
		glUniform1i(t_noiseTextureThree, 17);
		glActiveTexture(GL_TEXTURE0);
	}

	int t_noiseTextureFour = -1;
	if (rendererShaderData.getUniformLocation("t_noiseTextureFour", t_noiseTextureFour))
	{
		glActiveTexture(GL_TEXTURE0 + 18);
		glBindTexture(GL_TEXTURE_2D, noiseTextureFour);
		glUniform1i(t_noiseTextureFour, 18);
		glActiveTexture(GL_TEXTURE0);
	}
}

//	Initialize the Module Renderer.
void ModuleRenderer::initializeModuleRenderer()
{
	//	Enable Blending.
	glEnable(GL_BLEND);

	//	Enable Depth Test.
	glEnable(GL_DEPTH_TEST);
}

//	Initialize the Modules.
void ModuleRenderer::initializeModules()
{
	//	Create the GBuffer Module.
	gBufferModule = std::make_shared<GBufferModule>(this->shared_from_this());

	//	Create the Lights Module.
	lightsModule = std::make_shared<LightsModule>(this->shared_from_this());

	//	Create the Shadows Module.
	shadowsModule = std::make_shared<ShadowsModule>(this->shared_from_this(), lightsModule);

	//	SSAO Module.
	ssaoModule = std::make_shared<SSAOModule>(this->shared_from_this(), gBufferModule->viewWorldSpacePositionTexture(), gBufferModule->viewWorldSpaceVertexNormalAndDepthTexture(), gBufferModule->viewAmbientColorTexture(), gBufferModule->viewDepthTexture());

	//	Create the Deferred Pass Lighting Module.
	dPassLightingModule = std::make_shared<DPassLightingModule>(this->shared_from_this(), gBufferModule, lightsModule);

	//	Create the Forward Pass Lighting Module.
	//	fPassLightingModule = std::make_shared<FPassLightingModule>(renderableManager, dPassLightingModule);

	////	Bloom Module
	//bloomModule = std::make_shared<BloomModule>();

	////	HDR Module.
	//hdrModule = std::make_shared<HDRModule>();

	//	Create the Render to Screen Module.
	rtsModule = std::make_shared<RTSModule>(this->shared_from_this(), dPassLightingModule->viewDeferredPassLightingColorTexture());
}

//	Initialize the Noise Textures();
void ModuleRenderer::initializeNoiseTextures(unsigned int screenWidth, unsigned int screenHeight)
{
	GLubyte * pixelData = new GLubyte[screenWidth * screenHeight * 4];

	//	------------------------------------------------------------------------------------------------------------------------------	//
	//	Iterate and copy the pixels from the image.
	for (unsigned int i = 0; i < screenHeight; i++)
	{
		for (unsigned int j = 0; j < screenWidth; j++)
		{
			pixelData[((i * screenWidth + j) * 4) + 0] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 1] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 2] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 3] = (GLubyte)RNGs::doubleRand(0.0, 255.0);
		}
	}

	//	Generate the New Texture.
	glGenTextures(1, &noiseTextureOne);
	glBindTexture(GL_TEXTURE_2D, noiseTextureOne);

	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	Set the Texture parameters.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//	Bind it to the appropriate location.
	glBindTexture(GL_TEXTURE_2D, 0);


	//	------------------------------------------------------------------------------------------------------------------------------	//

	//	Iterate and copy the pixels from the image.
	for (unsigned int i = 0; i < screenHeight; i++)
	{
		for (unsigned int j = 0; j < screenWidth; j++)
		{
			pixelData[((i * screenWidth + j) * 4) + 0] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 1] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 2] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 3] = (GLubyte)RNGs::doubleRand(0.0, 255.0);
		}
	}

	glGenTextures(1, &noiseTextureTwo);
	glBindTexture(GL_TEXTURE_2D, noiseTextureTwo);

	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	Set the Texture parameters.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//	Bind it to the appropriate location.
	glBindTexture(GL_TEXTURE_2D, 0);


	//	------------------------------------------------------------------------------------------------------------------------------	//

	//	Iterate and copy the pixels from the image.
	for (unsigned int i = 0; i < screenHeight; i++)
	{
		for (unsigned int j = 0; j < screenWidth; j++)
		{
			pixelData[((i * screenWidth + j) * 4) + 0] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 1] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 2] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 3] = (GLubyte)RNGs::doubleRand(0.0, 255.0);
		}
	}



	glGenTextures(1, &noiseTextureThree);
	glBindTexture(GL_TEXTURE_2D, noiseTextureThree);

	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	Set the Texture parameters.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//	Bind it to the appropriate location.
	glBindTexture(GL_TEXTURE_2D, 0);


	//	------------------------------------------------------------------------------------------------------------------------------	//

	//	Iterate and copy the pixels from the image.
	for (unsigned int i = 0; i < screenHeight; i++)
	{
		for (unsigned int j = 0; j < screenWidth; j++)
		{
			pixelData[((i * screenWidth + j) * 4) + 0] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 1] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 2] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * screenWidth + j) * 4) + 3] = (GLubyte)RNGs::doubleRand(0.0, 255.0);
		}
	}


	glGenTextures(1, &noiseTextureFour);
	glBindTexture(GL_TEXTURE_2D, noiseTextureFour);

	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	Set the Texture parameters.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//	Bind it to the appropriate location.
	glBindTexture(GL_TEXTURE_2D, 0);

	//	------------------------------------------------------------------------------------------------------------------------------	//

}

//	Render the G Buffer Module.
void ModuleRenderer::renderGBufferModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	gBufferModule->render(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
}

//	Render the Lights Module.
void ModuleRenderer::renderLightsModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	lightsModule->render(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
}

//	Render the Shadows Module.
void ModuleRenderer::renderShadowsModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	shadowsModule->render(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
}

//	Render the Deferred Lighting Module.
void ModuleRenderer::renderDeferredLightingModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	dPassLightingModule->render(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
}

//	Render the Forward Lighting Module.
void ModuleRenderer::renderForwardLightingModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{

}

//	Render the SSAO Module.
void ModuleRenderer::renderSSAOModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	ssaoModule->render(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
}

//	Render the Render to Screen Module.
void ModuleRenderer::renderRTSModule(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	rtsModule->render(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
}


