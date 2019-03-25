#include "LayoutManager.h"

paint_tool::LayoutManager::LayoutManager() {
	//
}

paint_tool::LayoutManager::~LayoutManager() {
	//
}

void paint_tool::LayoutManager::layout(Component *component, LayoutStrategy parent_layout) {

	/* 1. align this component */

	switch (component->getAlignment()) {

	case LAYOUT_MANUAL :
		//
		break;

	case ALIGN_MIDDLE :

		if (parent_layout == LAYOUT_VERTICAL)
			component->positionCenter();
		else
		if (parent_layout == LAYOUT_HORIZONTAL)
			component->positionMiddle();

		break;

	case ALIGN_LEFT_OR_TOP :

		if (parent_layout == LAYOUT_VERTICAL)
			component->positionLeft();
		else
		if (parent_layout == LAYOUT_HORIZONTAL)
			component->positionTop();

		break;

	case ALIGN_RIGHT_OR_BOTTOM :

		if (parent_layout == LAYOUT_VERTICAL)
			component->positionRight();
		else
		if (parent_layout == LAYOUT_HORIZONTAL)
			component->positionBottom();

		break;
	}

	/* 2. determine if this is a group. if yes, then start laying out its
	      child components */
	
	if (component->isComponentGroup()) {

		ComponentGroup *group =
			dynamic_cast<ComponentGroup *>(component);

		if (group) {

			LayoutStrategy this_layout = group->getLayoutStrategy();
			
			switch (this_layout) {

			case LAYOUT_MANUAL:

				for (p_component_t &component : *group->getChildComponents())
					layout(component.get(), this_layout);

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

		layout(component.get(), group->getLayoutStrategy());
	}
}

void paint_tool::LayoutManager::layoutHorizontally(ComponentGroup *group) {

	int last_right = 0;

	for (p_component_t &component : *group->getChildComponents()) {

		component->setPosition(POINT{
			last_right,
			component->getPosition().y
			});

		layout(component.get(), group->getLayoutStrategy());

		last_right = component->getRect().right;
	}
}