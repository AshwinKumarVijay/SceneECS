#pragma once

#include <string>
#include "glm\glm.hpp"
#include "../ResourceData.h"

//	
class MaterialData : public ResourceData
{

public:

	//	Default Material Data Constructor.
	MaterialData();

	//	Default Material Data Destructor.
	~MaterialData();

	//	Return the Diffuse Albedo.
	glm::vec4 getDiffuseAlbedo() const;

	//	Set the Diffuse Albedo.
	void setDiffuseAlbedo(const glm::vec4 & newDiffuseAlbedo);

	//	Return the Specular Albedo.
	glm::vec4 getSpecularAlbedo() const;

	//	Set the Specular Albedo.
	void setSpecularAlbedo(const glm::vec4 & newSpecularAlbedo);

	//	Return the Emissive Color.
	glm::vec4 getEmissiveColor() const;

	//	Set the Emissive Color.
	void setEmissiveColor(const glm::vec4 & newEmissiveColor);

	//	Return the MRFO.
	glm::vec4 getMRFO() const;

	//	Set the MRFO.
	void setMRFO(const glm::vec4 & newMRFO);

	//	The Diffuse Albedo Texture - No Default Diffuse Albedo Texture.
	std::string diffuseAlbedoTexture;

	//	The Specular Albedo Map - No Default Specular Albedo Map.
	std::string specularAlbedoTexture;

	//	The Metallicness, Roughness, Fresnel and Opacity.
	std::string MRFOTexture;

	//	The Normal Map - No Default Normal Map.
	std::string normalTexture;

	//	The Occlusion Map - No Default Occlusion Map.
	std::string occlusionTexture;

private:

	//	The Diffuse Albedo Color.
	glm::vec4 diffuseAlbdeo;

	//	The Specular Albedo Color.
	glm::vec4 specularAlbedo;

	//	The Emissive Color.
	glm::vec4 emissiveColor;

	//	Metallic, Roughness and Opacity.
	glm::vec4 mrfo;
};
