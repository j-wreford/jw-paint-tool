#include "InteractiveComponent.h"

paint_tool::InteractiveComponent::InteractiveComponent(
	const	std::string	&id,
	const	POINT		&position,
	const	std::string &style_set_id
) : Component(id, position, style_set_id) {
	//
}

paint_tool::InteractiveComponent::InteractiveComponent(
	const	std::string	&id,
	const	POINT		&position,
	const	SIZE		&size,
	const	std::string &style_set_id
) : Component(id, position, size, style_set_id) {
	//
}

paint_tool::InteractiveComponent::~InteractiveComponent() {
	//
}

bool paint_tool::InteractiveComponent::hitTest(const POINT &mouse) {

	bool hit = PtInRect(&getRect(), mouse);

	if (hit)
		onHitTestPassed(mouse);

	return hit;
}

void paint_tool::InteractiveComponent::onMouseMove(const POINT &mouse) {

	if (focused && draggable)
		setPosition(mouse);
}