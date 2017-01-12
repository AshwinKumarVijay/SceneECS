#pragma once

#include <vector>

#include "../ECS/Component/Component.h"


class HierarchyComponent : public Component
{
public:

	/**

	Name: HierarchyComponent
	Parameters: -
	Purpose: Default HierarchyComponent Constructor
	Return Value: -
	Other Output: -

	*/
	HierarchyComponent();

	/**

	Name: ~HierarchyComponent
	Parameters: -
	Purpose: Default HierarchyComponent Destructor
	Return Value: -
	Other Output: -

	*/
	virtual ~HierarchyComponent();


	/**

	Name: setParent
	Parameters:
	- "newParent" - (int) (const) (&) - The new parent of the component.
	Purpose: Set the parent of this component. Does not add this entity to the list of the children of the parent.
	Return Value: -
	Other Output: -

	*/
	void setParent(const long int & newParent);

	/**

	Name: getParent
	Parameters: -
	Purpose: Return the parent of this Entity.
	Return Value: 
	- (long int) - If there is no parent -1. Otherwise, the value representing the entity of the integer.
	Other Output: -

	*/
	long int getParent() const;


	/**

	Name: unParent
	Parameters: -
	Purpose: Set the parent of this Entity to be -1.
	Return Value: -
	Other Output: -

	*/
	void unParent();



	/**

	Name: addChild
	Parameters:
	- "newChild" - (long int) (const) (&) - Remove a particular child, specified by ID.
	Purpose: Adds a particular child to the list of children, after checking if it is already a child. Does not set the parentID of the child.
	Return Value: -
	Other Output: Adds a child to the list.

	*/
	void addChild(const long int & newChild);


	/**

	Name: removeChild
	Parameters:
	- "removeChild" - (long int) (const) (&) - Remove a particular child, specified by ID.
	Purpose: Removes a particular child from the list of children. Does not change the parentID of the child.
	Return Value: -
	Other Output: Removes the child to the list.

	*/
	void removeChild(const long int & deadChild);



	/**

	Name: hasChild
	Parameters:
	- "queryChild" - (long int) (const) (&) - The ID representing which child we are looking for.
	Purpose: Returns a boolean value representing whether or not this entity has a child with that ID.
	Return Value:
	- (bool) - True:  This entity has a child with that ID / False: This entity has a child with that ID.
	Other Output: -

	*/
	bool hasChild(const long int & queryChild) const;


	/**

	Name: getChildEntities
	Parameters: -
	Purpose: Returns the vector of children, in a const array.
	Return Value:
	- (const vector<const long int>) - List of Child Entities.
	Other Output: -

	*/
	const std::vector<long int> & getChildEntities() const;


private:

	//	ID of the parent: -1 if there is no parent.
	long int parentID;

	//	List of Child Entities .
	std::vector<long int> childEntities;

};

