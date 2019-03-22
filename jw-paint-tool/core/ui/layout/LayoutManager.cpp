#include "LayoutManager.h"

paint_tool::LayoutManager::LayoutManager() {
	//
}

paint_tool::LayoutManager::~LayoutManager() {
	//
}

void paint_tool::LayoutManager::layout(Component *component) {

	/* 1. align this component */

	switch (component->getAlignment()) {

	case LAYOUT_MANUAL :
		//
		break;

	case ALIGN_LEFT_OR_TOP :
		
		/* need to know parent layout strategy to decide
		   on which method to call */

		if (true)
			component->positionLeft();
		else
			component->positionTop();

		break;

	case ALIGN_RIGHT_OR_BOTTOM :

		/* need to know parent layout strategy to decide
		   on which method to call */

		if (true)
			component->positionRight();
		else
			component->positionBottom();

		break;
	}

	/* 2. determine if this is a group. if yes, then start laying out its
	      child components */
	
	if (component->isComponentGroup()) {

		ComponentGroup *group =
			dynamic_cast<ComponentGroup *>(component);

		if (group) {
			
			switch (group->getLayoutStrategy()) {

			case LAYOUT_MANUAL:
				//
				break;

			case LAYOUT_VERTICAL:
				layoutVertically(group);
				break;

			case LAYOUT_HORIZONTAL:
				layoutHorizontally(group);
				break;
			}
		}
	}
}

void paint_tool::LayoutManager::layoutVertically(ComponentGroup *group) {

	int last_bottom = 0;

	for (p_component_t &component : *group->getChildComponents()) {

		component->setPosition(POINT{
			component->getPosition().x,
			last_bottom
		});

		last_bottom = component->getRect().bottom;

		layout(component.get());
	}
}

void paint_tool::LayoutManager::layoutHorizontally(ComponentGroup *group) {

	int last_right = 0;

	for (p_component_t &component : *group->getChildComponents()) {

		component->setPosition(POINT{
			last_right,
			component->getPosition().y
			});

		last_right = component->getRect().right;

		layout(component.get());
	}
}