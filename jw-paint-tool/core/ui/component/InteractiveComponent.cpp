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

	hovered = true;

	if (lmouse_down && active && draggable) {

		POINT new_pos{
			mouse.x - lmouse_down_offset.x,
			mouse.y - lmouse_down_offset.y
		};

		setPosition(new_pos);
	}
}

POINT paint_tool::InteractiveComponent::getRelativePoint(const POINT &mouse) const {

	POINT relative_point = mouse;

	POINT pos = getAbsolutePosition();

	relative_point.x -= pos.x;
	relative_point.y -= pos.y;

	POINT origin = getOrigin();

	relative_point.x -= origin.x;
	relative_point.y -= origin.y;

	return relative_point;

	/*
	return POINT{
		mouse.x - par_pos.x,//pos.x - par_origin.x,
		mouse.y - par_pos.y//pos.y - par_origin.y
	};*/
}