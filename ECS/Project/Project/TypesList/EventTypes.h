#pragma once

enum class EventType : long int
{
	ECS_NO_EVENT = -1,

	//	ECS Events.
	ECS_START_EVENT = 0,
	ECS_PAUSE_EVENT = 1,
	ECS_SHUTDOWN_EVENT = 2,

	//	Entity Events.
	ENTITY_CREATED = 3,
	ENTITY_ACTIVATED = 4,
	ENTITY_DEACTIVATED = 5,
	ENTITY_DESTROYED = 6,

	//	Component Events.
	COMPONENT_ADDED = 7,
	COMPONENT_CHANGED = 8,
	COMPONENT_DESTROYED = 9,

	//	Resource Event.
	RESOURCE_EVENT = 10,

	//	Input Event.
	INPUT_EVENT = 11,

	//	Interaction Event
	INTERACTION_EVENT = 12
};