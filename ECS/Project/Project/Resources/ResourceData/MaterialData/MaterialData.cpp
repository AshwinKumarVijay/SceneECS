#include "MaterialData.h"


//	Default MaterialData Constructor
MaterialData::MaterialData()
{
	//	The Diffuse Albedo Color.
	diffuseAlbdeo = glm::vec4(1.0);

	//	The Specular Albedo Color.
	specularAlbedo = glm::vec4(1.0);

	//	The Emissive Color.
	emissiveColor = glm::vec4(0.0);

	//	Metallic, Roughness and Opacity.
	metallicRoughnessFresnelOpacity = glm::vec4(1.0, 1.0, 1.0, 1.0);

	//	The Diffuse Albedo Map - No Default Diffuse Albedo Map.
	DiffuseAlbedoMap = "NONE";

	//	The Specular Albedo Map - No Default Specular Albedo Map.
	SpecularAlbedoMap = "NONE";

	//	The Metallicness, Roughness, Fresnel and Opacity.
	MRFOMap = "NONE";

	//	The Normal Map - No Default Normal Map.
	NormalMap = "NONE";

	//	The Occlusion Map - No Default Occlusion Map.
	OcclusionMap = "NONE";

}

//	Default MaterialData Destructor
MaterialData::~MaterialData()
{

}