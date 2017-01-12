#include "HierarchyComponent.h"


//	Default HierarchyComponent Constructor - pass the appropriate values to the Component.
HierarchyComponent::HierarchyComponent() 
	: Component(ComponentType::HIERARCHY_COMPONENT, ComponentTypeRequirement::HIERARCHY_COMPONENT_REQUIREMENTS)
{
	parentID = -1;
}

//	Default HierarchyComponent Destructor
HierarchyComponent::~HierarchyComponent()
{


}

//	Set the parentID;
void HierarchyComponent::setParent(const long int & newParent)
{
	parentID = newParent;
}

//	Return the parentID;
long int HierarchyComponent::getParent() const
{
	return parentID;
}

//	Unparent this entity. (Does not remove this entity from the child list of that parent)
void HierarchyComponent::unParent()
{
	parentID = -1;
}

//	Add a child to this entity. (Does not mark that entity as being parented to this entity)
void HierarchyComponent::addChild(const long int & newChild)
{
	if (!(hasChild(newChild)))
	{
		childEntities.push_back(newChild);
	}
}

void HierarchyComponent::removeChild(const long int & deadChild)
{
	if (hasChild(deadChild))
	{
		for (unsigned int i = 0; i < childEntities.size(); i++)
		{
			if (childEntities[i] == deadChild)
			{
				childEntities[i] = childEntities[childEntities.size() - 1];
				childEntities.pop_back();
			}
		}
	}
}

//	Check if this HierarchyComponent has the child specified by ID.
bool HierarchyComponent::hasChild(const long int & queryChild) const
{
	for (auto currentChild : childEntities)
	{
		if (currentChild == queryChild)
		{
			return true;
		}
	}

	return false;
}

//	Return the vector of the child entites.
const std::vector<long int> & HierarchyComponent::getChildEntities() const
{
	return childEntities;
}

