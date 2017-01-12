#pragma once

#include <vector>

#include "../ECS/Component/Component.h"

class GeometryComponent : public Component
{
public:

	/**

	Name: GeometryComponent
	Parameters: -
	Purpose: Default GeometryComponent Constructor
	Return Value: -
	Other Output: -

	*/
	GeometryComponent();


	/**

	Name: ~GeometryComponent
	Parameters: -
	Purpose: Default GeometryComponent Destructor
	Return Value: -
	Other Output: -

	*/
	virtual ~GeometryComponent();

	/**

	Name: setGeometryType
	Parameters:
	- "newGeometryType" - (string) (const) (&) - The new geometry type.
	Purpose: Set the geometry associated with this Renderable.
	Return Value: -
	Other Output: -

	*/
	virtual void setGeometryType(const std::string & newGeometryType);


	/**

	Name: getGeometryType
	Parameters:
	Purpose: Return the geometry associated with this Renderable.
	Return Value:
	- (int) - The type of the geometry associated.
	Other Output: -

	*/
	virtual std::string getGeometryType() const;


private:

	//	The Geometry associated with the Component.
	std::string geometryType;

};

