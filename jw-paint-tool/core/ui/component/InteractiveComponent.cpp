#include "InteractiveComponent.h"

paint_tool::InteractiveComponent::InteractiveComponent(
	const	std::string	&id,
	const	std::string &style_set_id
) : Component(id, style_set_id),
	focused(false),
	active(false),
	hovered(false),
	draggable(false) {
	//
}

paint_tool::InteractiveComponent::InteractiveComponent(
	const	std::string	&id,
	const	SIZE		&size,
	const	std::string &style_set_id
) : Component(id, size, style_set_id),
	focused(false),
	active(false),
	hovered(false),
	draggable(false) {
	//
}

paint_tool::InteractiveComponent::~InteractiveComponent() {
	//
}

// If the left mouse button is down, then active should be true.
// Does lmouse_down need to be a parameter here?
void paint_tool::InteractiveComponent::onMouseMoveHit(const POINT &mouse, const bool& lmouse_down) {

	/* this component was hovered over - set hovered to true and handle dragging if warrented */

	hovered = true;

	if (active && draggable) {

		setPosition(POINT{
			mouse.x + getPosition().x - lmd_startpoint.x,
			mouse.y + getPosition().y - lmd_startpoint.y
		});
	}
}

POINT paint_tool::InteractiveComponent::getRelativePoint(const POINT &mouse) const {

	POINT pos = getPosition();
	POINT origin = getOrigin();

	return POINT{
		mouse.x - pos.x - origin.x,
		mouse.y - pos.y - origin.y
	};

	/*
	return POINT{
		mouse.x - par_pos.x,//pos.x - par_origin.x,
		mouse.y - par_pos.y//pos.y - par_origin.y
	};*/
}