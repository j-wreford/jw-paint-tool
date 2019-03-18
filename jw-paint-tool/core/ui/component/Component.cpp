#include "Component.h"

paint_tool::Component::Component(
	const	std::string	&id,
	const	POINT		&position,
	const	std::string &style_set_id
) :
	id(id),
	rect(RECT{0, 0, 0, 0}),
	parent(nullptr),
	style_set_id(style_set_id) {

	setPosition(position);
}

paint_tool::Component::Component(
	const	std::string	&id,
	const	POINT		&position,
	const	SIZE		&size,
	const	std::string &style_set_id
) : Component(id, position, style_set_id) {

	setSize(size);
}

paint_tool::Component::~Component() {
	//
}

RECT paint_tool::Component::getAbsoluteRect() const {

	RECT abs_rect;
	::SetRect(&abs_rect, rect.left, rect.top, rect.right, rect.bottom);

	if (parent) {

		SIZE size = getSize();
		POINT pos = getPosition();
		POINT par_pos = parent->getAbsolutePosition();

		abs_rect.left = par_pos.x + pos.x;
		abs_rect.top = par_pos.y + pos.y;
		abs_rect.right = par_pos.x + pos.x + size.cx;
		abs_rect.bottom = par_pos.y + pos.y + size.cy;
	}

	return abs_rect;
}

POINT paint_tool::Component::getAbsolutePosition() const {

	POINT abs_pos = {
		rect.left,
		rect.top
	};

	if (parent) {

		POINT par_pos = parent->getAbsolutePosition();

		abs_pos.x += par_pos.x;
		abs_pos.y += par_pos.y;
	}

	return abs_pos;
}

void paint_tool::Component::setPosition(POINT position) {

	SIZE size = getSize();

	SetRect(
		&rect,
		position.x,
		position.y,
		position.x + size.cx,
		position.y + size.cy
	);

	if (parent)
		parent->recalculateSize();
}

void paint_tool::Component::setSize(SIZE size) {

	SetRect(
		&rect,
		rect.left,
		rect.top,
		rect.left + size.cx,
		rect.top + size.cy
	);

	if (parent)
		parent->recalculateSize();
}