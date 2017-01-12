#include "SceneComponentMaker.h"

#include "../../Components/HierarchyComponent/HierarchyComponent.h"
#include "../../Components/TransformComponent/TransformComponent.h"
#include "../../Components/CameraComponent/CameraComponent.h"
#include "../../Components/GeometryComponent/GeometryComponent.h"
#include "../../Components/LightComponent/LightComponent.h"
#include "../../Components/RenderingComponent/RenderingComponent.h"
#include "../../Components/SelectionComponent/SelectionComponent.h"
#include "../../Components/MovementResponseComponent/MovementResponseComponent.h"


//	Default SceneComponentMaker Constructor.
SceneComponentMaker::SceneComponentMaker()
{

}


//	Default SceneComponentMaker Destructor.
SceneComponentMaker::~SceneComponentMaker()
{

}

//	Create a component of the specified component type, and return a pointer to it. NULL is returned if the component type was not recognized.
std::shared_ptr<Component> SceneComponentMaker::createComponent(const ComponentType & componentType)
{
	//	Request the Component from the ComponentMaker.
	std::shared_ptr<Component> newComponent = NULL;

	switch (componentType)
	{

		//	Check for HIERARCHY Component Type.
	case ComponentType::HIERARCHY_COMPONENT:
	{
		newComponent = std::make_shared<HierarchyComponent>();
		break;
	}

	//	Check for TRANSFORM Component Type.
	case ComponentType::TRANSFORM_COMPONENT:
	{
		newComponent = std::make_shared<TransformComponent>();
		break;
	}

	//	Check for CAMERA Component Type.
	case ComponentType::CAMERA_COMPONENT:
	{
		newComponent = std::make_shared<CameraComponent>();
		break;
	}


	//	Check for GEOMETRY Component Type.
	case ComponentType::GEOMETRY_COMPONENT:
	{
		newComponent = std::make_shared<GeometryComponent>();
		break;
	}

	//	Check for RENDERING Component Type.
	case ComponentType::RENDERING_COMPONENT:
	{
		newComponent = std::make_shared<RenderingComponent>();
		break;
	}

	case ComponentType::LIGHT_COMPONENT:
	{
		newComponent = std::make_shared<LightComponent>();
		break;
	}

	//	Check for SELECTION Component Type.
	case ComponentType::SELECTION_COMPONENT:
	{
		newComponent = std::make_shared<SelectionComponent>();
		break;
	}

	//	Check for MOVEMENT RESPONSE Component Type.
	case ComponentType::MOVEMENT_RESPONSE_COMPONENT:
	{
		newComponent = std::make_shared<MovementResponseComponent>();
		break;
	}

	//	Set the New Component to NULL if No Case Matches, and throw an error.
	default:
	{
		newComponent = NULL;
		throw "Error. SceneComponentMaker: Create Component. No Matching Component Type Found!";
		break;
	}

	}

	//	Return the New Component.
	return newComponent;
}

//	Return the ComponentTypeRequirements corresponding to the ComponentType passed in.
long int SceneComponentMaker::getComponentTypeRequirements(const ComponentType & componentType)
{

	//	Switch on the Component Type.
	switch (componentType)
	{

		//	Check for HIERARCHY Component Type.
	case ComponentType::HIERARCHY_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::HIERARCHY_COMPONENT_REQUIREMENTS);
		break;
	}

	//	Check for TRANSFORM Component Type.
	case ComponentType::TRANSFORM_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::TRANSFORM_COMPONENT_REQUIREMENTS);
		break;
	}

	//	Check for CAMERA Component Type.
	case ComponentType::CAMERA_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::CAMERA_COMPONENT_REQUIREMENTS);
		break;
	}

	//	Check for the SPEED Component Type.
	case ComponentType::SPEED_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::SPEED_COMPONENT_REQUIREMENTS);
		break;
	}

	//	Check for the GEOMETRY Component Type.
	case ComponentType::GEOMETRY_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::GEOMETRY_COMPONENT_REQUIREMENTS);
		break;
	}

	//	Check for the RENDERING Component Type.
	case ComponentType::RENDERING_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::RENDERING_COMPONENT_REQUIREMENTS);
		break;
	}

	//	Check for the LIGHT Component Type.
	case ComponentType::LIGHT_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::LIGHT_COMPONENT_REQUIREMENTS);
		break;
	}

	//	Check for the SELECTION Component Type.
	case ComponentType::SELECTION_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::SELECTION_COMPONENT_REQUIREMENTS);
		break;
	}

	//	Check for the MOVEMENT RESPONSE Component Type.
	case ComponentType::MOVEMENT_RESPONSE_COMPONENT:
	{
		return (long int)(ComponentTypeRequirement::MOVEMENT_RESPONSE_COMPONENT_REQUIREMENTS);
		break;
	}

	//	If the Type was not recognized.
	default:
		throw "Error. SceneComponentMaker: Get Component Type Requirements. No Matching Component Type Found!";
		return 0;
		break;
	}

}

bool SceneComponentMaker::checkHasComponentRequirements(const long int & currentAttachedComponentSignature, const ComponentType & componentType)
{
	//	Get the Component Type Requirements.
	long int componentTypeRequirements = getComponentTypeRequirements(componentType);

	//	Return whether the Attached Components fulfils the required Component Type.
	return (currentAttachedComponentSignature & componentTypeRequirements) == componentTypeRequirements;
}

//	Check if Component Type B is dependent on Component Type A. (That is, Component Type A was required when Component Type B was added.)
bool SceneComponentMaker::checkComponentTypeDependency(const ComponentType & componentTypeA, const ComponentType & componentTypeB)
{
	//	Check if the Component Types are the same.
	if (componentTypeA == componentTypeB)
	{
		//	Return false if they are.
		return false;
	}
	else
	{
		//	Return the result of the check.
		return (((long int)componentTypeA & getComponentTypeRequirements(componentTypeB)) == (long int)componentTypeA);
	}
}


