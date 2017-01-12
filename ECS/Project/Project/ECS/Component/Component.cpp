#include "Component.h"

//	Default Component Constructor
Component::Component(const ComponentType & newComponentTypeSignature, const ComponentTypeRequirement & newComponentTypeRequirementsSignature)
{

	componentTypeSignature =  newComponentTypeSignature;
	componentTypeRequirementsSignature = newComponentTypeRequirementsSignature;
}

//	Default Component Destructor
Component::~Component()
{


}

//	Return a Component Type Signature - the type signature of this component.
ComponentType Component::getComponentTypeSignature() const
{
	return componentTypeSignature;
}

//	Return a Component Type Requirements Signature - the list of types required to attach a component of current type. 
ComponentTypeRequirement Component::getComponentTypeRequirementsSignature() const
{
	return componentTypeRequirementsSignature;
}
