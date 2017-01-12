#include "TransformComponent.h"
#include "../../Transform/Transform.h"

//	Default TransformComponent Constructor - pass the appropriate values to the Component.
TransformComponent::TransformComponent()
	: Component(ComponentType::TRANSFORM_COMPONENT, ComponentTypeRequirement::TRANSFORM_COMPONENT_REQUIREMENTS)
{
	transform = std::make_shared<Transform>();
}

//	Default Transform Destructor
TransformComponent::~TransformComponent()
{

}

//	Return the associated Transform.
std::shared_ptr<Transform> TransformComponent::getTransform()
{
	return transform;
}


//	Return the associated Transform.
std::shared_ptr<const Transform> TransformComponent::viewTransform() const
{
	return transform;
}
