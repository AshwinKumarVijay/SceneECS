#pragma once

#include <vector>
#include <map>
#include <memory>

#include "../TypesList/ComponentTypes.h"

class EventQueue;
class EventReceiver;
class EventDispatcher;
class Entity;

class Component;
class HierarchyComponent;
class TransformComponent;
class RenderingComponent;
class SpeedComponent;
class GeometryComponent;
class CameraComponent;
class SelectionComponent;

class ComponentMaker;

class EntityManager
{
	
public:
	
	//	Default EntityManager Constructor
	EntityManager(std::shared_ptr<ComponentMaker> newComponentMaker, std::shared_ptr<EventQueue> newEventQueue);

	//	Default EntityManager Constructor
	virtual ~EntityManager();

	//	Creates and adds and Entity to the list of Entites, and returns the associated EntityID.
	long int createEntity();

	//	Return whether or not the Entity exists.
	bool doesEntityExist(const long int & givenEntity) const;

	//	Sets the state of the specified Entity to be active.
	void activateEntity(const long int & givenEntity);

	//	Sets the state of the specified Entity to be inactive.
	void deactivateEntity(const long int & givenEntity);

	//	Destroys the specified entity.
	void destroyEntity(const long int & givenEntity);
	
	//	Returns the Component Signature of the Entity, and -1 if there is no Entity.
	long int getEntityComponentSignature(const long int & givenEntity) const;

	//	Adds a component of the specified type to the specified entity, if one does not exist already. Returns a pointer to the component (the new one if one was added) or NULL, if one existed, if there is no specified entity or if it is an invalid type.
	std::shared_ptr<Component> addComponentToEntity(const long int & givenEntity, const ComponentType & componentType);

	//	A shared_ptr to the const Component of the specifed type, of the specified Entity. NULL if there is no such component.
	std::shared_ptr<const Component> viewComponentOfEntity(const long int & givenEntity, const ComponentType & componentTypeSignature) const;

	//	Return a pointer to to the Component of the specified type, of the specified Entity and notifies all systems that the component was changed (if it exists). Null if there is no such component.
	std::shared_ptr<Component> getComponentOfEntity(const long int & givenEntity, const ComponentType & componentTypeSignature, const std::string & requestingSystemSignature) const;

	// True if the specified Entity has all the Components in the query / False if any of them are missing, or if there is no such Entity.
	bool hasComponents(const long int & givenEntity, const long int & componentTypesQuery) const;

	//	Removes a Component of the specified type from the givenEntity, and all components that depended on the component.
	void removeComponentFromEntity(const long int & givenEntity, const ComponentType & componentTypeSignature);

	//	Return a list of all the entities with the components of the specified type, or NULL if there are no entities.
	std::shared_ptr<std::vector<long int>> getEntitiesWithComponentOfType(const ComponentType & componentTypeSignature) const;

	//	Update the Entity Manager.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Clean out the Entity Manager, and destroy all entities.
	virtual void cleanEntityManager();


private:

	//	Return a pointer to the Entity and NULL if there is no such entity.
	std::shared_ptr<Entity> getEntity(const long int & givenEntity) const;

	//	Create a component of the specified component type, and return a pointer to it. NULL is returned if the component type was not recognized.
	std::shared_ptr<Component> createComponent(const ComponentType & componentType);

	//	Check if the specified entity has the required components for the specified component type.
	bool checkComponentRequirements(const long int & givenEntity, const ComponentType & componentType);
	
	//	Return the ComponentTypeRequirements corresponding to the ComponentType passed in.
	long int getComponentTypeRequirements(const ComponentType & componentType);

	//	Add the Entity to the Component Type List, creating a list if none exists.
	virtual void addEntityToComponentTypeList(const long int & givenEntity, const ComponentType & componentType);

	//	Remove the Entity from the Component Type List, destroying the list if it becomes empty.
	virtual void removeEntityFromComponentTypeList(const long int & givenEntity, const ComponentType & componentType);

	//	Remove the all the Components that are of a Component Type that required the specified Component Type to be added to this entity.
	virtual void removeComponentTypeDependencies(const long int & givenEntity, const ComponentType & componentType);

	//	Check if Component Type B is dependent on Component Type A. (That is, Component Type A was required when Component Type B was added.)
	virtual bool checkComponentTypeDependency(const ComponentType & componentTypeA, const ComponentType & componentTypeB);

	// The last entity identity created.
	long int lastEntityID;

	//	The list of Entities.
	std::map<long int, std::shared_ptr<Entity>> mapIDToEntity;

	//	The list of Entities that have been destroyed.
	std::vector<long int> destroyedEntities;

	//	Map of the Component Type to the Vector of Entities.
	std::map<ComponentType, std::shared_ptr<std::vector<long int>>>  mapEntityComponentType;

	//	The Event Dispatcher to Dispatch Events to the Event Queue.
	std::shared_ptr<EventDispatcher> eventDispatcher;

	//	The Event Receiver to Receive Events from the Event Queue.
	std::shared_ptr<EventReceiver> eventReceiver;

	//	The Component Maker to construct the Commponents.
	std::shared_ptr<ComponentMaker> componentMaker;

};

