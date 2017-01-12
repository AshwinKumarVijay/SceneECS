#include "SelectionComponent.h"


//	Default SelectedComponent Constructor
SelectionComponent::SelectionComponent()
	:Component(ComponentType::SELECTION_COMPONENT, ComponentTypeRequirement::SELECTION_COMPONENT_REQUIREMENTS)
{
	selected = false;
}

//	Default SelectedComponent Destructor
SelectionComponent::~SelectionComponent()
{


}

//	Return whether this component is currently selected.
bool SelectionComponent::getSelected() const
{
	return selected;
}

//	Select this component.
void SelectionComponent::select()
{
	selected = true;
}


//	Deselect this component.
void SelectionComponent::deselect()
{
	selected = false;
}
