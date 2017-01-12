#pragma once

//	Component Types
enum class ComponentType : long int
{
	//	No Component
	NO_COMPONENT = 0,

	//	Hierarchy Component - Only Required Component Type.
	HIERARCHY_COMPONENT = 2,

	//	Transform Component.
	TRANSFORM_COMPONENT = 4,

	//	Geometry Component.
	GEOMETRY_COMPONENT = 8,

	//	Rendering Component.
	RENDERING_COMPONENT = 16,

	//	Light Component.
	LIGHT_COMPONENT = 32,

	//	Physics Component.
	PHYSICS_COMPONENT = 64,

	//	Camera Component.
	CAMERA_COMPONENT = 128,

	//	Speed Component.
	SPEED_COMPONENT = 256,

	//	Selected Component.
	SELECTION_COMPONENT = 512,
	
	//	Movement Response Component.
	MOVEMENT_RESPONSE_COMPONENT = 1024
};

//	The Requirements for each Component Types.
enum class ComponentTypeRequirement : long int
{
	//	No Requirements for the Hierarchy Component.
	HIERARCHY_COMPONENT_REQUIREMENTS 
		= (long int) ComponentType::NO_COMPONENT,
	
	// TRANSFORM - Requires only a Hierarchy Component.
	TRANSFORM_COMPONENT_REQUIREMENTS 
		= (long int) ComponentType::HIERARCHY_COMPONENT,
	
	//	GEOMETRY - Require a Hierarchy and a Transform Component.
	GEOMETRY_COMPONENT_REQUIREMENTS
		= (long int) ComponentType::HIERARCHY_COMPONENT
		| (long int) ComponentType::TRANSFORM_COMPONENT,
	
	//	RENDERING - Requires a Hierarchy, Transform and a Geometry Component.
	RENDERING_COMPONENT_REQUIREMENTS
	= (long int)ComponentType::HIERARCHY_COMPONENT
	| (long int)ComponentType::TRANSFORM_COMPONENT
	| (long int)ComponentType::GEOMETRY_COMPONENT,

	//	LIGHT - Requires a Hierarchy, Transform
	LIGHT_COMPONENT_REQUIREMENTS
	= (long int)ComponentType::HIERARCHY_COMPONENT
	| (long int)ComponentType::TRANSFORM_COMPONENT,


	//	PHYSICS - Requires a Hierarchy, Transform and a Geometry Component.
	PHYSICS_COMPONENT_REQUIREMENTS
	= (long int)ComponentType::HIERARCHY_COMPONENT
	| (long int)ComponentType::TRANSFORM_COMPONENT
	| (long int)ComponentType::GEOMETRY_COMPONENT,

	//	CAMERA - Requires a Hierarchy and a Transform Component.
	CAMERA_COMPONENT_REQUIREMENTS
	= (long int)ComponentType::HIERARCHY_COMPONENT
	| (long int)ComponentType::TRANSFORM_COMPONENT,

	//	SPEED - Requires a Hierarchy and a Transform Component.
	SPEED_COMPONENT_REQUIREMENTS
	= (long int)ComponentType::HIERARCHY_COMPONENT
	| (long int)ComponentType::TRANSFORM_COMPONENT,

	//	MOVEMENT RESPONSE - Requires a Hierarchy and a Transform Component.
	MOVEMENT_RESPONSE_COMPONENT_REQUIREMENTS
	= (long int)ComponentType::HIERARCHY_COMPONENT
	| (long int)ComponentType::TRANSFORM_COMPONENT,

	//	SELECTION - Requires a Hierarchy and a Transform Component.
	SELECTION_COMPONENT_REQUIREMENTS
	= (long int)ComponentType::HIERARCHY_COMPONENT
	| (long int)ComponentType::TRANSFORM_COMPONENT

};