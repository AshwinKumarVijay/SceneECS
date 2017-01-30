#pragma once
#include "../ECS/Component/Component.h"

class LightComponent : public Component
{

public:

	//	Default LightComponent Constructor.
	LightComponent();

	//	Default LightComponent Destructor.
	virtual ~LightComponent();



	//	Set whether the Light is Active.
	virtual void setActive(const bool & newActive);

	//	Return whether the Light is Active.
	virtual bool getActive() const;


	//	Set whether the Shadows are Active.
	virtual void setShadows(const bool & newShadows);

	//	Return whether the Light casts Shadows.
	virtual bool getShadows() const;



	//	Set the Light Color And Intensity.
	virtual void setLightColorAndIntensity(const glm::vec4 & newLightColorAndIntensity);

	//	Return the Light Color amnd Intensity.
	virtual glm::vec4 getLightColorAndIntensity() const;


	//	Set the Light Distance Attenuation.
	virtual void setLightDistanceAttenuation(const glm::vec4 & newLightDistanceAttenuation);

	//	Return the Light Distance Attenuation.
	virtual glm::vec4 getLightDistanceAttenuation() const;

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

