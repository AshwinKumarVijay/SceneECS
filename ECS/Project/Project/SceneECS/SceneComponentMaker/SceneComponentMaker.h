#pragma once
#include "../../ECS/ComponentMaker/ComponentMaker.h"

class SceneComponentMaker : public ComponentMaker
{

public:

	//	Default SceneComponentMaker Constructor.
	SceneComponentMaker();

	//	Default SceneComponentMaker Destructor.
	virtual ~SceneComponentMaker();

	//	Create a component of the specified component type, and return a pointer to it. NULL is returned if the component type was not recognized.
	virtual std::shared_ptr<Component> createComponent(const ComponentType & componentType);

	//	Return the ComponentTypeRequirements corresponding to the ComponentType passed in.
	virtual long int getComponentTypeRequirements(const ComponentType & componentType);

	//	Check whether the provided Attached Component Signature has all the requriements for adding a Component of the specified type.
	virtual bool checkHasComponentRequirements(const long int & currentAttachedComponentSignature, const ComponentType & componentType);

	//	Check if Component Type B is dependent on Component Type A. (That is, Component Type A was required when Component Type B was added.)
	virtual bool checkComponentTypeDependency(const ComponentType & componentTypeA, const ComponentType & componentTypeB);


private:


};

