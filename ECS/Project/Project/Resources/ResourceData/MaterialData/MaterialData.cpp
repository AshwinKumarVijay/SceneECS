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
	mrfo = glm::vec4(1.0, 1.0, 1.0, 1.0);

	//	The Diffuse Albedo Map - No Default Diffuse Albedo Map.
	diffuseAlbedoTexture = "NONE";

	//	The Specular Albedo Map - No Default Specular Albedo Map.
	specularAlbedoTexture = "NONE";

	//	The Metallicness, Roughness, Fresnel and Opacity.
	MRFOTexture = "NONE";

	//	The Normal Map - No Default Normal Map.
	normalTexture = "NONE";

	//	The Occlusion Map - No Default Occlusion Map.
	occlusionTexture = "NONE";

}

//	Default MaterialData Destructor
MaterialData::~MaterialData()
{

}

//	Return the Diffuse Albedo.
glm::vec4 MaterialData::getDiffuseAlbedo() const
{
	return diffuseAlbdeo;
}

//	Set the Diffuse Albedo.
void MaterialData::setDiffuseAlbedo(const glm::vec4 & newDiffuseAlbedo)
{
	diffuseAlbdeo = newDiffuseAlbedo;
}

//	Return the Specular Albedo.
glm::vec4 MaterialData::getSpecularAlbedo() const
{
	return specularAlbedo;
}

//	Set the Specular Albedo.
void MaterialData::setSpecularAlbedo(const glm::vec4 & newSpecularAlbedo)
{
	specularAlbedo = newSpecularAlbedo;
}

//	Return the Emissive Color.
glm::vec4 MaterialData::getEmissiveColor() const
{
	return emissiveColor;
}

//	Set the Emissive Color.
void MaterialData::setEmissiveColor(const glm::vec4 & newEmissiveColor)
{
	emissiveColor = newEmissiveColor;
}

//	Return the MRFO Color.
glm::vec4 MaterialData::getMRFO() const
{
	return mrfo;
}

//	Set the MRFO.
void MaterialData::setMRFO(const glm::vec4 & newMRFO)
{
	mrfo = newMRFO;
}
