#pragma once

#include <vector>
#include <memory>

#include "../TypesList/EventTypes.h"
#include "../TypesList/EntityState.h"
#include "../TypesList/InputTypes.h"
#include "../TypesList/ComponentTypes.h"
#include "../TypesList/ResourceTypes.h"

class Component;

class Entity
{
public:


	/**

	Name: Entity
	Parameters: (long int) ID - The ID of this Entity
	Purpose: Default Entity Constructor
	Return Value: -
	Other Output: -

	*/

	Entity(const long int & newID);


	/**

	Name: ~Entity
	Parameters: -
	Purpose: Default Entity Destructor
	Return Value: -
	Other Output: -

	*/

	virtual ~Entity();


	/**

	Name: getID
	Parameters: -
	Purpose: Returns the ID of this Entity.
	Return Value: 
	- (long int) - ID
	Other Output: -

	*/

	long int getID() const;


	/**

	Name: getActive
	Parameters: -
	Purpose: Return the whether this Entity is active.
	Return Value:
	- (bool) - True, if active / False, if not active.
	Other Output: -

	*/
	bool getActive() const;


	/**

	Name: activate
	Parameters: -
	Purpose: Mark this Entity as active for processing in the systems.
	Return Value: -
	Other Output: -

	*/
	void activate();

	/**

	Name: getInactive
	Parameters: -
	Purpose: Return the whether this Entity is inactive.
	Return Value:
	- (bool) - True, if inactive / False, if not inactive.
	Other Output: -

	*/
	bool getInactive() const;


	/**

	Name: deactivate
	Parameters: -
	Purpose: Mark this Entity as inactive for processing in the systems. (Should not be processed).
	Return Value: -
	Other Output: -

	*/
	void deactivate();


	/**

	Name: getDestroyed
	Parameters: -
	Purpose: Return the whether this Entity is destroyed.
	Return Value:
	- (bool) - True, if destroyed / False, if not destroyed.
	Other Output: -

	*/
	bool getDestroyed() const;


	/**

	Name: destroy
	Parameters: -
	Purpose: Mark this Entity as destroyed for processing in the systems. (Should not be processed, and has been destroyed).
	Return Value: -
	Other Output: -

	*/
	void destroy();


	/**

	Name: getAttachedComponentsSignature
	Parameters: -
	Purpose: Returns the Signature representing all the attached Components.
	Return Value:
	- (long int) - The integer signature representing the attached components.
	Other Output: -

	*/
	long int getAttachedComponentsSignature() const;

	
	/**

	Name: addComponent
	Parameters:
	- "Component" - (shared_ptr<Component>) - shared_ptr to the pointer that is to be attached to this entity.
	Purpose: Adds a Component of the specified type to this Entity, if there is not one already. Updates the attachedComponentString
	Return Value: -
	Other Output: -

	*/
	void addComponent(std::shared_ptr<Component> newComponent);


	/**

	Name: hasComponents
	Parameters:
	- "componentTypesQuery" - (long int) (const) - The Types of the Components to be checked for.
	Purpose: Check whether the specified entity has all the components specifed by the query.
	Return Value:
	- (bool) - True if the Entity has all the Components /	False if any of them are missing, or if there is no such Entity.
	Other Output: -

	*/
	bool hasComponents(const long int & componentTypesQuery) const;


	/**

	Name: getComponentByType
	Parameters:
	- "componentType" - (ComponentType) (const) (&) - The Type of the Component.
	Purpose: -
	Return Value:
	- (shared_ptr<Component>) - Return a pointer to the component specified by the componentType.
	Other Output: -

	*/
	std::shared_ptr<Component> getComponentByType(const ComponentType & componentType) const;

	/**

	Name: getAttachedComponentTypes
	Parameters: -
	Purpose: Return a pointer to the a vector of the attached ComponentTypes.
	Return Value:
	- (shared_ptr<const vector<ComponentType>>) - A pointer to the a vector of the attached ComponentTypes.
	Other Output: -

	*/
	std::shared_ptr<const std::vector<ComponentType>> getAttachedComponentTypes();

	/**

	Name: removeComponent
	Parameters:
	- "componentType" - (ComponentType) (const) (&) - The Types of the Component to be removed.
	Purpose: Removes the specifed componentType from this Entity
	Return Value: -
	Other Output: -

	*/
	void removeComponent(const ComponentType & componentType);



private:

	//	The ID of this Entity.
	long int ID;

	//	Current Entity State.
	EntityState entityState;

	//	Bit string of attached Components.
	long int attachedComponentsSignature;

	//	The List of Attached Components.
	std::vector<std::shared_ptr<Component>> attachedComponents;

	//	The List of the Attached Component Types.
	std::shared_ptr<std::vector<ComponentType>> attachedComponentTypes;
};

