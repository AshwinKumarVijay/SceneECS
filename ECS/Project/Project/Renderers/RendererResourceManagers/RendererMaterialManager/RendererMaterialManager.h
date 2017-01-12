#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "glm\glm.hpp"

class MaterialData;

struct RendererMaterialData
{
	//	The Diffuse Albedo Color.
	glm::vec4 diffuseAlbedo = glm::vec4(1.0);

	//	The Specular Albedo Color.
	glm::vec4 specularAlbedo = glm::vec4(1.0);

	//	The Emissive Color.
	glm::vec4 emissiveColor = glm::vec4(0.0);

	//	Metallic, Roughness and Opacity.
	glm::vec4 metallicRoughnessFresnelOpacity = glm::vec4(1.0, 1.0, 1.0, 1.0);

	//	The Diffuse Albedo Map - No Default Diffuse Albedo Map.
	std::string diffuseAlbedoMap = "NONE";

	//	The Specular Albedo Map - No Default Specular Albedo Map.
	std::string specularAlbedoMap = "NONE";

	//	The Metallic Roughness Fresnel Opacity Map.
	std::string MRFOMap = "NONE";

	//	The Normal Map - No Default Normal Map.
	std::string normalMap = "NONE";

	//	The Occlusion Map - No Default Occlusion Map.
	std::string occlusionMap = "NONE";

};

class RendererMaterialManager
{

public:

	//	Default RendererMaterialManager Constructor.
	RendererMaterialManager();

	//	Default RendererMaterialManager Destructor.
	virtual ~RendererMaterialManager();

	//	Add a new Material from provided MaterialData and the Material Name.
	virtual void addMaterial(const std::string & newMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData);

	//	View the Material of the specified Name.
	std::shared_ptr<const RendererMaterialData> viewMaterial(const std::string & requestedMaterialName) const;

	//	Update the Material of the Material Name and the specified Material Data.
	virtual void updateMaterial(const std::string & requestedMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData);

	//	Delete the Material of the specified Name.
	virtual void deleteMaterial(const std::string & deadMaterialName);

private:

	//	Map of the Material Names to the Material Data.
	std::map <std::string, std::shared_ptr<RendererMaterialData>> mapNameToMaterialData;

};

