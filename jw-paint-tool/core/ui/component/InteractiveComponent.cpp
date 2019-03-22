#include "InteractiveComponent.h"

paint_tool::InteractiveComponent::InteractiveComponent(
	const	std::string	&id,
	const	std::string &style_set_id
) : Component(id, style_set_id),
	focused(false),
	active(false),
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
	draggable(false) {
	//
}

paint_tool::InteractiveComponent::~InteractiveComponent() {
	//
}

void paint_tool::InteractiveComponent::onLeftMouseButtonDown(const POINT &mouse) {

	if (wasHit(mouse)) {

		active = true;

		lmouse_down_offset = POINT{
			mouse.x - getPosition().x,
			mouse.y - getPosition().y
		};
	}
	else
		focused = false;
}

void paint_tool::InteractiveComponent::onLeftMouseButtonUp(const POINT &mouse) {

	if (wasHit(mouse))
		focused = true;

	lmouse_down_offset = POINT{ -1, -1 };

	active = false;
}

void paint_tool::InteractiveComponent::onMouseMove(const POINT &mouse, const bool& lmouse_down) {

	if (lmouse_down && active && draggable) {

		POINT new_pos = //getPosition();
		{
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