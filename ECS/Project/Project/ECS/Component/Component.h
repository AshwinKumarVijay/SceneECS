#pragma once

#include <vector>
#include <memory>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\quaternion.hpp"

#include "glm\gtc\matrix_inverse.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "../TypesList/ComponentTypes.h"

class GeometryManager;
class MaterialManager;
class TextureManager;


class Component
{
public:


	
	/**

	Name: Component
	Parameters:
	- "newComponentTypeSignature" - (ComponentTypes) (const) (&) - Set the type of this component.
	- "newComponentTypeRequirementsSignature" - (ComponentTypeRequirements) (const) (&) - Set the requirements of this signature component.
	Purpose: Default Component Constructor
	Return Value: -
	Other Output: -

	*/
	Component(const ComponentType & newComponentTypeSignature, const ComponentTypeRequirement & newComponentTypeRequirementsSignature);

	/**

	Name: ~Component
	Parameters: -
	Purpose: Default Component Destructor
	Return Value: -
	Other Output: -

	*/

	virtual ~Component();


	/**

	Name: getComponentTypeSignature
	Parameters: -
	Purpose: Returns the signature associated with this type of Component.
	Return Value: -
	Other Output: -

	*/
	ComponentType getComponentTypeSignature() const;


	/**

	Name: getComponentTypeRequirementsSignature
	Parameters: -
	Purpose: Returns the signature associated with the requirements of this type of Component
	Return Value: -
	Other Output: -

	*/
	ComponentTypeRequirement getComponentTypeRequirementsSignature() const;



private:

	//	The Signature of the this Type Of Component.
	ComponentType componentTypeSignature;

	//	The Signature of the Requirements for this type of Component.
	ComponentTypeRequirement componentTypeRequirementsSignature;
	
};

