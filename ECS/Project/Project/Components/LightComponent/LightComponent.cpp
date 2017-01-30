#include "LightComponent.h"


//	Default LightComponent Constructor.
LightComponent::LightComponent()
	: Component(ComponentType::LIGHT_COMPONENT, ComponentTypeRequirement::LIGHT_COMPONENT_REQUIREMENTS)
{

}

//	Default LightComponent Constructor.
LightComponent::~LightComponent()
{

}

//	Set whether the Light is Active.
void LightComponent::setActive(const bool & newActive)
{
	active = newActive;
}

//	Return whether the Light is Active.
bool LightComponent::getActive() const
{
	return active;
}

//	Set whether the Shadows are Active.
void LightComponent::setShadows(const bool & newShadows)
{
	shadows = newShadows;
}

//	Return whether the Light casts Shadows.
bool LightComponent::getShadows() const
{
	return shadows;
}

//	Set the Light Color And Intensity.
void LightComponent::setLightColorAndIntensity(const glm::vec4 & newLightColorAndIntensity)
{
	lightColorAndIntensity = newLightColorAndIntensity;
}

//	
glm::vec4 LightComponent::getLightColorAndIntensity() const
{
	return lightColorAndIntensity;
}

//	Set the Light Distance Attenuation.
void LightComponent::setLightDistanceAttenuation(const glm::vec4 & newLightDistanceAttenuation)
{
	lightDistanceAttenuation = newLightDistanceAttenuation;
}

//	
glm::vec4 LightComponent::getLightDistanceAttenuation() const
{
	return lightDistanceAttenuation;
}
