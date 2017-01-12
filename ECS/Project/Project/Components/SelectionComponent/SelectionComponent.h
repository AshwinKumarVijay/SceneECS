#pragma once

#include "../ECS/Component/Component.h"

class SelectionComponent : public Component
{

public:

	//	Add Comments - TO DO
	SelectionComponent();

	//	Add Comments - TO DO
	virtual ~SelectionComponent();

	//	Add Comments - TO DO
	bool getSelected() const;

	//	Add Comments - TO DO
	virtual void select();

	//	Add Comments - TO DO
	virtual void deselect();


private:

	//	Add Comments - TO DO
	bool selected;

};

