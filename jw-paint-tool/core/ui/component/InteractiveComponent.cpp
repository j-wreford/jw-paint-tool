#include "InteractiveComponent.h"

paint_tool::InteractiveComponent::InteractiveComponent(
	const	std::string	&id,
	const	POINT		&position,
	const	std::string &style_set_id
) : Component(id, position, style_set_id),
	focused(false),
	active(false),
	draggable(false) {
	//
}

paint_tool::InteractiveComponent::InteractiveComponent(
	const	std::string	&id,
	const	POINT		&position,
	const	SIZE		&size,
	const	std::string &style_set_id
) : Component(id, position, size, style_set_id),
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

		setPosition(POINT{
			mouse.x - lmouse_down_offset.x,
			mouse.y - lmouse_down_offset.y
		});
	}
}

POINT paint_tool::InteractiveComponent::getRelativePoint(const POINT &mouse) const {

	POINT pos = getAbsolutePosition();

	return POINT{
		mouse.x - pos.x,
		mouse.y - pos.y
	};
}