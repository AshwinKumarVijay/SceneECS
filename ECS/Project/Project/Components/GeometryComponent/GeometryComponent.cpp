#include "GeometryComponent.h"



//	Default GeometryComponent Constructor
GeometryComponent::GeometryComponent()
	: Component(ComponentType::GEOMETRY_COMPONENT, ComponentTypeRequirement::GEOMETRY_COMPONENT_REQUIREMENTS)
{
	geometryType = "DEFAULT GEOMETRY";

}


//	Default GeometryComponent Destructor
GeometryComponent::~GeometryComponent()
{

}

//	Set the Geometry Name associated with this Renderable.
void GeometryComponent::setGeometryType(const std::string & newGeometryType)
{
	geometryType = newGeometryType;
}

//	Return the Geometry. 
std::string GeometryComponent::getGeometryType() const
{
	return geometryType;
}
