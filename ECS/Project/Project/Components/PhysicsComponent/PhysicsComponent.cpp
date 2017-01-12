#include "PhysicsComponent.h"
#include "../../Resources/ResourceData/PhysicsData/PhysicsData.h"

//	Default PhysicsComponent Constructor
PhysicsComponent::PhysicsComponent()
	: Component(ComponentType::PHYSICS_COMPONENT, ComponentTypeRequirement::PHYSICS_COMPONENT_REQUIREMENTS)
{
	
}


//	Default PhysicsComponent Destructor
PhysicsComponent::~PhysicsComponent()
{

}
