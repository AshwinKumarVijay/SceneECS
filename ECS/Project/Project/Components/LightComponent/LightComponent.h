#pragma once
#include "../ECS/Component/Component.h"

class LightComponent : public Component
{

public:

	//	Default LightComponent Constructor.
	LightComponent();

	//	Default LightComponent Destructor.
	virtual ~LightComponent();

	//	Return whether the Light is Active.
	virtual bool getActive();

	//	Return whether the Light casts Shadows.
	virtual bool getShadows();

	//	Return the Light Color amnd Intensity.
	virtual glm::vec4 getLightColorAndIntensity();

	//	Return the Light Distance Attenuation.
	virtual glm::vec4 getLightDistanceAttenuation();

private:

	//	Whether the Light is Active.
	bool active;
	
	//	Whether the Light Casts Shadows.
	bool shadows;

	//	The Color of the Light.
	glm::vec4 lightColorAndIntensity;

	//	The Attenuation of the Light.
	glm::vec4 lightDistanceAttenuation;

};

