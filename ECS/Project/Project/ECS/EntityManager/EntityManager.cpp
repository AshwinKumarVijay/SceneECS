#include "EntityManager.h"

#include "../EventQueue/EventQueue.h"
#include "../DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "Entity\Entity.h"

#include "../Component/Component.h"
#include "../ComponentMaker/ComponentMaker.h"

//	Default EntityManager Constructor
EntityManager::EntityManager(std::shared_ptr<ComponentMaker> newComponentMaker, std::shared_ptr<EventQueue> newEventQueue)
{
	componentMaker = newComponentMaker;
	eventDispatcher = std::make_shared<EventDispatcher>(newEventQueue);
	eventReceiver = std::make_shared<EventReceiver>();
	newEventQueue->addReceiver(eventReceiver);

	lastEntityID = 0;
}

//	Default EntityManager Destructor
EntityManager::~EntityManager()
{
	//	Destroy all the Entities.
	for (auto itr = mapIDToEntity.begin(); itr != mapIDToEntity.end(); itr++)
	{
		destroyEntity(itr->first);
	}

	//	Clear the Event Dispatcher.
	eventDispatcher = NULL;

	//	Clear the Event Receiver.
	eventReceiver = NULL;
}

//	Return the ID of the newly created entity.
long int EntityManager::createEntity()
{
	//	Check if there are any destroyed entties we can reuse.
	if (destroyedEntities.size() == 0)
	{
		//	Create a new one if there are no available ones.
		long int currentEntity = lastEntityID;

		//	Create an appropriate new entity.	
		mapIDToEntity[currentEntity] = std::make_shared<Entity>(currentEntity);

		//	
		lastEntityID++;

		//	Dispatch the Event to the Queue.
		eventDispatcher->dispatchToEventQueue(EventType::ENTITY_CREATED, "ENTITY_MANAGER", ComponentType::NO_COMPONENT, currentEntity);

		//	Return the associated entity.
		return currentEntity;
	}
	else
	{
		//	Reuse an available entity
		long int currentEntity = destroyedEntities.back();

		//	Remove the destroyed entity.
		destroyedEntities.pop_back();

		//	Create an appropriate new entity.	
		mapIDToEntity[currentEntity] = std::make_shared<Entity>(currentEntity);

		//	Dispatch the Event to the Queue.
		eventDispatcher->dispatchToEventQueue(EventType::ENTITY_CREATED, "ENTITY_MANAGER", ComponentType::NO_COMPONENT, currentEntity);

		//	Return the associated entity.
		return currentEntity;
	}
}

//	Return whether the Entity exists.
bool EntityManager::doesEntityExist(const long int & givenEntity) const
{
	//	Find the Entity Corresponding to the specified ID.
	auto itr = mapIDToEntity.find(givenEntity);

	//	Check if there is an Entity with that ID
	if (itr == mapIDToEntity.end())
	{
		return false;
	}
	else
	{
		//	Check if the Entity has not been destroyed.
		if (itr->second->getDestroyed())
		{
			//	Return false if the Entity has been destroyed.
			return false;
		}
		else
		{
			//	Otherwise, Return true.
			return true;
		}
	}
}

//	Activate the specified Entity.
void EntityManager::activateEntity(const long int & givenEntity)
{
	//	Check if the Entity exists.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);
	if (entity != NULL)
	{
		//	Activate the entity only if it is currently inactive.
		if (entity->getInactive())
		{
			//	Dispatch the Event to the Queue.
			eventDispatcher->dispatchToEventQueue(EventType::ENTITY_ACTIVATED, "ENTITY_MANAGER", ComponentType::NO_COMPONENT, givenEntity);

			//	Activate the Entity.
			entity->activate();
		}

	}
}

//	Deactivate the specified Entity.
void EntityManager::deactivateEntity(const long int & givenEntity)
{
	//	Check if the Entity exists.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);
	if (entity != NULL)
	{
		//	Check if the Entity is active.
		if (entity->getActive())
		{
			//	Dispatch the Event to the Queue.
			eventDispatcher->dispatchToEventQueue(EventType::ENTITY_DEACTIVATED, "ENTITY_MANAGER", ComponentType::NO_COMPONENT, givenEntity);

			//	Deactivate the Entity.
			entity->deactivate();
		}
	}
}

//	Destroy the specified Entity.
void EntityManager::destroyEntity(const long int & givenEntity)
{
	//	Check if the Entity exists.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);
	if (entity != NULL)
	{
		//	Check if the Entity is active or inactive.
		if (entity->getActive() || entity->getInactive())
		{
			//	Check the Attached Component Types.
			std::shared_ptr<const std::vector<ComponentType>> attachedComponentTypes = entity->getAttachedComponentTypes();

			//	Iterate over the attached component types.
			for (int i = 0; i < attachedComponentTypes->size(); i++)
			{
				ComponentType currentComponentType = attachedComponentTypes->operator[](i);
				removeComponentFromEntity(givenEntity, currentComponentType);
			}

			//	Dispatch the Event to the Queue.
			eventDispatcher->dispatchToEventQueue(EventType::ENTITY_DESTROYED, "ENTITY_MANAGER", ComponentType::NO_COMPONENT, givenEntity);

			//	Deactivate the Entity.
			entity->destroy();
		}
	}
}

//	Return the Entity Component Signature.
long int EntityManager::getEntityComponentSignature(const long int & givenEntity) const
{
	//	Find the Entities, that have the Component of the specified type.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);
	if (entity != NULL)
	{
		if (entity->getDestroyed())
		{
			//	Return no component.
			return (long int)ComponentType::NO_COMPONENT;
		}
		else
		{
			//	Return the entities with the specified type.
			return entity->getAttachedComponentsSignature();
		}
	}
	else
	{
		//	Return no component if the entity does not exist.
		return (long int)ComponentType::NO_COMPONENT;
	}
}

//	Add a component of the specified type to the Entity
std::shared_ptr<Component> EntityManager::addComponentToEntity(const long int & givenEntity, const ComponentType & componentType)
{
	//	Find the Entities, that have the Component of the specified type.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);

	//	Check if the entity exists.
	if (entity != NULL)
	{
		//	Check if the entity has already been destroyed.
		if (entity->getDestroyed())
		{
			return NULL;
		}
		else
		{
			//	Check if it already has the component.
			if (entity->hasComponents((long int)componentType))
			{
				return entity->getComponentByType(componentType);
			}
			else
			{
				//	Check if it has the appropriate components.
				if (checkComponentRequirements(givenEntity, componentType))
				{
					//	Add the component.
					std::shared_ptr<Component> newComponent = createComponent(componentType);
					if (newComponent != NULL)
					{
						//	Add the appropriate component.
						entity->addComponent(newComponent);

						//	Dispatch the Event to the EventQueue.
						eventDispatcher->dispatchToEventQueue(EventType::COMPONENT_ADDED, "ENTITY_MANAGER", componentType, givenEntity);

						//	Add the entity to the list of entities having this component.
						addEntityToComponentTypeList(givenEntity, componentType);

						//	Return the new component.
						return newComponent;
					}
					else
					{
						//	Return NULL if a new component is created.
						return NULL;
					}
				}
				else
				{
					//	Return NULL if the component requirements are not met.
					return NULL;
				}
			}
		}
	}
	else
	{
		//	Return NULL if the Entity is NULL.
		return NULL;
	}
}

//	Return a pointer to view the component of an Entity.
std::shared_ptr<const Component> EntityManager::viewComponentOfEntity(const long int & givenEntity, const ComponentType & componentTypeSignature) const
{
	//	Return the entity and check if it exists.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);

	//	Check if the entity is NULL.
	if (entity != NULL)
	{
		//	Check if the entity has already been destroyed.
		if (entity->getDestroyed())
		{
			//	If the Entity was destroyed, return false.
			return NULL;
		}
		else
		{
			//	Return the entities with the specified type.
			return entity->getComponentByType(componentTypeSignature);
		}
	}
	else
	{
		//	If the entity was never created, return NULL.
		return NULL;
	}
}

//	Return a pointer to get the component of an Entity.
std::shared_ptr<Component> EntityManager::getComponentOfEntity(const long int & givenEntity, const ComponentType & componentTypeSignature, const std::string & requestingSystemSignature) const
{
	//	Return the entity and check if it exists.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);
	if (entity != NULL)
	{
		//	Check if the entity has already been destroyed.
		if (entity->getDestroyed())
		{
			//	If the Entity was destroyed, return false.
			return NULL;
		}
		else
		{
			//	Check if the entity has the component.
			if (entity->hasComponents((long int)componentTypeSignature))
			{
				//	Dispatch the Event to the EventQueue.
				eventDispatcher->dispatchToEventQueue(EventType::COMPONENT_CHANGED, requestingSystemSignature, componentTypeSignature, givenEntity);

				//	If it does have the component, return it.
				return entity->getComponentByType(componentTypeSignature);
			}
			else
			{
				//	If it does not have the component, return NULL.
				return NULL;
			}
		}
	}
	else
	{
		//	If the entity was never created, return NULL.
		return NULL;
	}
}

//	Check if the specified entity has the requested components.
bool EntityManager::hasComponents(const long int & givenEntity, const long int & componentTypesQuery) const
{
	//	Return the entity and check if it exists.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);
	if (entity != NULL)
	{
		//	Check if the entity has already been destroyed.
		if (entity->getDestroyed())
		{
			//	If the Entity was destroyed, return false.
			return false;
		}
		else
		{
			//	If the Entity exists, check if the entity has the components.
			return entity->hasComponents(componentTypesQuery);
		}
	}
	else
	{
		//	If the Entity does not exist, return false.
		return false;
	}
}

//	Remove the component from the entity.
void EntityManager::removeComponentFromEntity(const long int & givenEntity, const ComponentType & componentTypeSignature)
{
	//	Return the entity and check if it exists.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);
	if (entity != NULL)
	{
		//	Check if the entity has already been destroyed.
		if (!entity->getDestroyed())
		{
			//	Check if the entity has the requested component.
			if (entity->hasComponents((long int)componentTypeSignature))
			{
				//	Check for Component Dependency.
				removeComponentTypeDependencies(givenEntity, componentTypeSignature);

				//	Find the entity and remove it from the list of entities.
				removeEntityFromComponentTypeList(givenEntity, componentTypeSignature);

				//	Dispatch the Event to the EventQueue.
				eventDispatcher->dispatchToEventQueue(EventType::COMPONENT_DESTROYED, "ENTITY_MANAGER", componentTypeSignature, givenEntity);

				//	Remove the appropriate component.
				entity->removeComponent(componentTypeSignature);
			}
		}
	}
}

//	Return a vector of entities that have the Component of the specified type, or NULL if there are no entities.
std::shared_ptr<std::vector<long int>> EntityManager::getEntitiesWithComponentOfType(const ComponentType & componentTypeSignature) const
{
	//	Find the Entities, that have the Component of the specified type.
	auto itr = mapEntityComponentType.find(componentTypeSignature);

	//	Return NULL, or the entities that have the component type requested.
	if (itr == mapEntityComponentType.end())
	{
		//	If there are no entities with the specified type.
		return NULL;
	}
	else
	{
		//	Return the entities with the specified type.
		return itr->second;
	}
}

//	Update the Entity Manager.
void EntityManager::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	eventReceiver->clearEvents();
}

//	Clean the Entity Manager.
void EntityManager::cleanEntityManager()
{
	//	Iterate over the Entity IDS.
	for (auto itr = mapIDToEntity.begin(); itr != mapIDToEntity.end(); itr++)
	{
		//	Destroy the Entities.
		destroyEntity(itr->first);
	}

	//	Clear away all the entities.
	destroyedEntities.clear();
}

//	Return a pointer to the specified entity.
std::shared_ptr<Entity> EntityManager::getEntity(const long int & givenEntity) const
{
	//	Find the Entities, that have the Component of the specified type.
	auto itr = mapIDToEntity.find(givenEntity);

	//	Return NULL, or the entities that have the component type requested.
	if (itr == mapIDToEntity.end())
	{
		//	If there are no entities with the specified type.
		return NULL;
	}
	else
	{
		//	Return the entities with the specified type.
		return itr->second;
	}
}

//	Create a component of the specifed type.
std::shared_ptr<Component> EntityManager::createComponent(const ComponentType & componentType)
{
	//	Request the Component from the ComponentMaker.
	std::shared_ptr<Component> newComponent = componentMaker->createComponent(componentType);

	//	Return the New Component.
	return newComponent;
}

//	Check if the specified entity has the required components for the specified component type.
bool EntityManager::checkComponentRequirements(const long int & givenEntity, const ComponentType & componentType)
{
	//	Get the Entity.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);

	//	Initialize to false.
	bool hasComponentRequirements = false;

	//	Check if the entity exists.
	if (entity != NULL)
	{
		//	Check if the entity was destroyed.
		if (!entity->getDestroyed())
		{
			return componentMaker->checkHasComponentRequirements(entity->getAttachedComponentsSignature(), componentType);
		}
		else
		{
			//	Set the Component Requirements Flag to false.
			hasComponentRequirements = false;
		}
	}
	else
	{
		//	Set the Component Requirements Flag to false.
		hasComponentRequirements = false;
	}

	//	Return whether or not we need the components.
	return hasComponentRequirements;
}

//	Return the Component Type Requirements for the Component Type.
long int EntityManager::getComponentTypeRequirements(const ComponentType & componentType)
{
	//	Use the ComponentMaker to return the Component Type Requirements for the Component Type.
	return componentMaker->getComponentTypeRequirements(componentType);
}

//	Add the Entity to the Component Type List.
void EntityManager::addEntityToComponentTypeList(const long int & givenEntity, const ComponentType & componentType)
{
	//	Find the list of the component type we are looking for.
	auto itr = mapEntityComponentType.find(componentType);

	//	Check whether this component type list exists.
	if (itr != mapEntityComponentType.end())
	{
		//	Add this entity to that list.
		itr->second->push_back(givenEntity);
	}
	else
	{
		//	Create a new list if the list does not exist.
		mapEntityComponentType[componentType] = std::make_shared<std::vector<long int>>();

		//	Return the entity.
		mapEntityComponentType[componentType]->push_back(givenEntity);
	}
}

//	Remove the Entity from the Component Type List.
void EntityManager::removeEntityFromComponentTypeList(const long int & givenEntity, const ComponentType & componentType)
{
	//	Find the list.
	auto itr = mapEntityComponentType.find(componentType);

	//	Check if the list exists.
	if (itr != mapEntityComponentType.end())
	{
		//	Iterate over the list.
		for (int i = 0; i < itr->second->size(); i++)
		{
			//	Check if this is the enttiy to delete.
			if (itr->second->operator[](i) == givenEntity)
			{
				//	Replace the entity entry in the last position.
				itr->second->operator[](i) = itr->second->operator[](itr->second->size() - 1);

				//	Pop back the entity entry.
				itr->second->pop_back();
			}
		}

		//	Check if the list is now emtpy.		
		if (itr->second->size() == 0)
		{
			//	Erase it from the map if it is.
			mapEntityComponentType.erase(itr);
		}
	}
}

//	Remove the all the Components that are of a Component Type that required the specified Component Type to be added to this entity.
void EntityManager::removeComponentTypeDependencies(const long int & givenEntity, const ComponentType & componentType)
{
	//	Return the entity and check if it exists.
	std::shared_ptr<Entity> entity = getEntity(givenEntity);
	if (entity != NULL)
	{
		//	Check if the entity has already been destroyed.
		if (!entity->getDestroyed())
		{
			//	Initialize to true. 
			bool hasDependentComponents = true;

			//	Keep removing components while there are still components that depend on the specified type.
			while (hasDependentComponents)
			{
				//	Recheck to see if we removed all dependent components.
				hasDependentComponents = false;

				//	Get the current list of attached component type.
				std::shared_ptr<const std::vector<ComponentType>> attachedComponentTypes = entity->getAttachedComponentTypes();

				//	Initialize the Dependent Component Type Index.
				int dependentComponentTypeIndex = -1;

				//	Iterate over the attached component types.
				for (int i = 0; i < attachedComponentTypes->size(); i++)
				{
					//	Check if the current component type is dependent on 
					if (checkComponentTypeDependency(componentType, attachedComponentTypes->at(i)))
					{
						//	Set the flag to indicate that we have found a dependent component/
						hasDependentComponents = true;

						//	Set the dependent component type index.
						dependentComponentTypeIndex = i;

						//	Exit the inner loop.
						break;
					}

				}

				//	Check if there are any dependent component.
				if (hasDependentComponents)
				{
					//	Remove the Component from Entity.
					removeComponentFromEntity(givenEntity, attachedComponentTypes->at(dependentComponentTypeIndex));
				}
			}
		}
	}
}

//	Check if Component Type B is dependent on Component Type A. (That is, Component Type A was required when Component Type B was added.)
bool EntityManager::checkComponentTypeDependency(const ComponentType & componentTypeA, const ComponentType & componentTypeB)
{
	//	Use the ComponentMaker to check if Component Type B is dependent on Component Type A. (That is, Component Type A was required when Component Type B was added.)
	return componentMaker->checkComponentTypeDependency(componentTypeA, componentTypeB);
}
