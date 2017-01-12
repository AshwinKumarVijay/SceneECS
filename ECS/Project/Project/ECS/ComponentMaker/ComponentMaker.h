#pragma once
#include <memory>

#include "../TypesList/ComponentTypes.h"

class Component;

class ComponentMaker
{

public:

	//	Default ComponentMaker Constructor.
	ComponentMaker();

	//	Default ComponentMaker Destructor.
	virtual ~ComponentMaker();

	//	Create a component of the specified component type, and return a pointer to it. NULL is returned if the component type was not recognized.
	virtual std::shared_ptr<Component> createComponent(const ComponentType & componentType) = 0;

	//	Return the ComponentTypeRequirements corresponding to the ComponentType passed in.
	virtual long int getComponentTypeRequirements(const ComponentType & componentType) = 0;

	//	Check whether the provided Attached Component Signature has all the requriements for adding a Component of the specified type.
	virtual bool checkHasComponentRequirements(const long int & currentAttachedComponentSignature, const ComponentType & componentType) = 0;

	//	Check if Component Type B is dependent on Component Type A. (That is, Component Type A was required when Component Type B was added.)
	virtual bool checkComponentTypeDependency(const ComponentType & componentTypeA, const ComponentType & componentTypeB) = 0;

private:


};

