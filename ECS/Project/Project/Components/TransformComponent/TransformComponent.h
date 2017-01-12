#pragma once

#include <vector>

#include "../ECS/Component/Component.h"

class Transform;

class TransformComponent : public Component
{

public:

	/**

	Name: TransformComponent
	Parameters: -
	Purpose: Default TransformComponent Constructor
	Return Value: -
	Other Output: -

	*/
	TransformComponent();

	/**

	Name: ~TransformComponent
	Parameters: -
	Purpose: Default ~TransformComponent Constructor
	Return Value: -
	Other Output: -

	*/
	virtual ~TransformComponent();



	/**

	Name: getTransform
	Parameters: -
	Purpose: Set the geometry associated with this Renderable.
	Return Value:
	- (shared_ptr<Transform>) - 
	Other Output: -

	*/
	std::shared_ptr<Transform> getTransform();
	
	/**

	Name: viewTransform
	Parameters: -
	Purpose: Set the geometry associated with this Renderable.
	Return Value:
	- (shared_ptr<const Transform>) -
	Other Output: -

	*/
	std::shared_ptr<const Transform> viewTransform() const;


private:

	//	The Transform associated with this TransformComponent
	std::shared_ptr<Transform> transform;

};

