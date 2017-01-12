#pragma once

//	Resource Event Types.
enum class ResourceEventType
{
	//	Resource Added.
	RESOURCE_ADDED = 0,

	//	Resource Updated.
	RESOURCE_UPDATED = 1,

	//	Resource Destroyed.
	RESOURCE_DESTROYED = 2,
};

//	Resource Type.
enum class ResourceType : int
{
	//	Geometry Resource Type
	GEOMETRY_RESOURCE = 8,

	//	Material Resource Type
	MATERIAL_RESOURCE = 16,

	//	Shader Resource Type
	SHADER_RESOURCE = 32,

	//	Texture Resource Type
	TEXTURE_RESOURCE = 64
};