#include "RenderingComponent.h"


//	Default RenderingComponent Constructor - pass the appropriate values to the Component.
RenderingComponent::RenderingComponent()
	: Component(ComponentType::RENDERING_COMPONENT, ComponentTypeRequirement::RENDERING_COMPONENT_REQUIREMENTS)
{
	renderableID = -1;
	materialType = "DEFAULT MATERIAL TYPE";
	shaderType = "DEFAULT SHADER TYPE";
	activeRendering = true;
}

//	Default RenderingComponent Destructor
RenderingComponent::~RenderingComponent()
{

}

//	Set the RenderableID.
void RenderingComponent::setRenderableID(const long int & newRenderableID)
{
	renderableID = newRenderableID;
}

//	Return the RenderableID.
long int RenderingComponent::getRenderableID() const
{
	return renderableID;
}

//	Set the Material Type associated with this Rendering Component.
void RenderingComponent::setMaterialType(const std::string & newMaterialType)
{
	materialType = newMaterialType;
}

//	Return the Material Type associated with this Rendering Component.
std::string RenderingComponent::getMaterialType() const
{
	return materialType;
}

//	Set the Shader Type associated with this Rendering Component.
void RenderingComponent::setShadingType(const std::string & newShaderType)
{
	shaderType = newShaderType;
}

//	Return the Shader Type associated with this Rendering Component.
std::string RenderingComponent::getShadingType() const
{
	return shaderType;
}

void RenderingComponent::setActiveRendering(const bool & newActiveRendering)
{
	activeRendering = newActiveRendering;
}

bool RenderingComponent::getActiveRendering() const
{
	return activeRendering;
}
