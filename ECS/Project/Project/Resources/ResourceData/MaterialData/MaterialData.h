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

	//	The Diffuse Albedo Color.
	glm::vec4 diffuseAlbdeo;

	//	The Specular Albedo Color.
	glm::vec4 specularAlbedo;

	//	The Emissive Color.
	glm::vec4 emissiveColor;

	//	Metallic, Roughness and Opacity.
	glm::vec4 metallicRoughnessFresnelOpacity;

	//	The Diffuse Albedo Map - No Default Diffuse Albedo Map.
	std::string DiffuseAlbedoMap;

	//	The Specular Albedo Map - No Default Specular Albedo Map.
	std::string SpecularAlbedoMap;

	//	The Metallicness, Roughness, Fresnel and Opacity.
	std::string MRFOMap;

	//	The Normal Map - No Default Normal Map.
	std::string NormalMap;

	//	The Occlusion Map - No Default Occlusion Map.
	std::string OcclusionMap;

};
