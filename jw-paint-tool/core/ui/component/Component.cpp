#include "Component.h"

paint_tool::Component::Component(
	const	std::string	&id,
	const	POINT		&position,
	const	int			&fg_colour,
	const	int			&bg_colour) :
	id(id),
	position(position),
	parent(nullptr),
	fg_colour(fg_colour), bg_colour(bg_colour) {
	//
}

paint_tool::Component::~Component() {
	//
}

POINT paint_tool::Component::getPosition() const {

	POINT pos = position;

	if (parent) {

		POINT parent_pos = parent->getPosition();

		pos.x += parent_pos.x;
		pos.y += parent_pos.y;
	}

	return pos;
}
