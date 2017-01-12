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

//	Return whether the Light is Active.
bool LightComponent::getActive()
{
	return active;
}

//	Return whether the Light casts Shadows.
bool LightComponent::getShadows()
{
	return shadows;
}

//	
glm::vec4 LightComponent::getLightColorAndIntensity()
{
	return lightColorAndIntensity;
}

//	
glm::vec4 LightComponent::getLightDistanceAttenuation()
{
	return lightDistanceAttenuation;
}
