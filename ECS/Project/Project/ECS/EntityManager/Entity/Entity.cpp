#include "Entity.h"
#include "../../Component/Component.h"

//	Default Entity Constructor
Entity::Entity(const long int & newID)
{
	//	Set the ID of this Entity.
	ID = newID;
	
	//	Set this Entity to be active.
	entityState = EntityState::ENTITY_ACTIVE;

	//	Set this Enttiy to have not attached components to begin with.
	attachedComponentsSignature = (long int)ComponentType::NO_COMPONENT;


	attachedComponentTypes = std::make_shared<std::vector<ComponentType>>();
}

//	Default Entity Destructor
Entity::~Entity()
{

}

long int Entity::getID() const
{
	return ID;
}

//	Return whether this Entity is active or not.
bool Entity::getActive() const
{
	return entityState == EntityState::ENTITY_ACTIVE;
}

//	Return whether this Entity is inactive or not.
bool Entity::getInactive() const
{
	return entityState == EntityState::ENTITY_INACTIVE;
}

//	Return whether this Entity is inactive or not.
bool Entity::getDestroyed() const
{
	return entityState == EntityState::ENTITY_DESTROYED;
}


//	Set this entity to be active.
void Entity::activate()
{
	entityState = EntityState::ENTITY_ACTIVE;
}

//	Set this entity to be inactive.
void Entity::deactivate()
{
	entityState = EntityState::ENTITY_INACTIVE;
}

void Entity::destroy()
{
	entityState = EntityState::ENTITY_DESTROYED;
	attachedComponentsSignature = (long int)ComponentType::NO_COMPONENT;
	attachedComponents.clear();
}

//	Return the Attached Component Signature.
long int Entity::getAttachedComponentsSignature() const
{
	return attachedComponentsSignature;
}


//	Add a Component to this Entity - aslo updates the attachedComponentsSignature.
void Entity::addComponent(std::shared_ptr<Component> newComponent)
{
	//	If the newComponent is not NULL.
	if (newComponent != NULL)
	{
		// Check if the Entity does not already have a component of this type
		if (!hasComponents((long int)newComponent->getComponentTypeSignature()))
		{
			attachedComponentsSignature = (long int)attachedComponentsSignature | (long int)newComponent->getComponentTypeSignature();
			attachedComponents.push_back(newComponent);
		}
	}
}


//	Checks if this Entity has the Components queried for.
bool Entity::hasComponents(const long int & componentTypesQuery) const
{
	//	Check if the entity has the Compnents have been queried for.
	if ((attachedComponentsSignature & componentTypesQuery) == componentTypesQuery)
	{
		//	Has the necessary components.
		return true;
	}
	else
	{
		//	Does not have the necessary components.
		return false;
	}
}

//	Remove the specified component type from this Entity.
void Entity::removeComponent(const ComponentType & componentType)
{
	if (hasComponents((long int)componentType))
	{
		for (unsigned int i = 0; i < attachedComponents.size(); i++)
		{
			//	Find the component pointer.
			if (attachedComponents[i]->getComponentTypeSignature() == componentType)
			{
				//	Replace it with the last pointer, and remove the last pointer.
				attachedComponents[i] = attachedComponents[attachedComponents.size() - 1];

				//	
				attachedComponents.pop_back();
			}
		}
	}

}

//	Return a Component of the specified type.
std::shared_ptr<Component> Entity::getComponentByType(const ComponentType & componentType) const
{
	//	Check each of the components.
	for (auto current_component : attachedComponents)
	{
		if (current_component->getComponentTypeSignature() == componentType)
		{
			return current_component;
		}
	}

	return NULL;
}

//	Return the vector of the Attached Component Types.
std::shared_ptr<const std::vector<ComponentType>> Entity::getAttachedComponentTypes()
{
	//	Clear the Attached Component Types.
	attachedComponentTypes->clear();

	//	Iterate over the attachedComponents.
	for (int i = 0; i < attachedComponents.size(); i++)
	{
		//	Construct the vector of Attached Components.
		attachedComponentTypes->push_back(attachedComponents[i]->getComponentTypeSignature());
	}
	
	//	Return the vector of the Attached Component Types.
	return attachedComponentTypes;
}
