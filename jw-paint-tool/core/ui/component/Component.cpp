#include "Component.h"

paint_tool::Component::Component(
	const	std::string	&id,
	const	POINT		&position,
	const	std::string &style_set_id
) :
	id(id),
	rect(RECT{ 0, 0, 0, 0 }),
	origin(POINT{ 0, 0 }),
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

	RECT abs_rect = getRect();

	if (parent) {

		SIZE size = getSize();
		POINT pos = getPosition();
		POINT par_origin = parent->getOrigin();

		POINT par_pos = parent->getAbsolutePosition();

		abs_rect.left = par_pos.x + par_origin.x + pos.x;
		abs_rect.top = par_pos.y + par_origin.y + pos.y;
		abs_rect.right = par_pos.x + pos.x + size.cx;
		abs_rect.bottom = par_pos.y + pos.y + size.cy;
	}

	return abs_rect;
}

POINT paint_tool::Component::getAbsolutePosition() const {


	POINT abs_pos = getPosition();

	if (parent) {

		POINT par_pos = parent->getAbsolutePosition();
		POINT par_origin = parent->getOrigin();

		abs_pos.x += par_origin.x + par_pos.x;
		abs_pos.y += par_origin.y + par_pos.y;
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

void paint_tool::Component::positionRight() {

	SIZE par_size{ 0,0 };

	if (parent)
		par_size = parent->getSize();

	setPosition(POINT{
		par_size.cx - getSize().cx,
		getPosition().y
	});
}

void paint_tool::Component::positionCenter() {
	
	SIZE par_size{ 0,0 };

	if (parent)
		par_size = parent->getSize();

	int space = (par_size.cx - getSize().cx) / 2;

	setPosition(POINT{
		space,
		getPosition().y
	});
}

void paint_tool::Component::positionBottom() {

	SIZE par_size{ 0,0 };

	if (parent)
		par_size = parent->getSize();

	setPosition(POINT{
		getPosition().x,
		par_size.cy - getSize().cy
	});
}

void paint_tool::Component::positionMiddle() {
	
	SIZE par_size{ 0,0 };

	if (parent)
		par_size = parent->getSize();

	int space = (par_size.cy - getSize().cy) / 2;

	setPosition(POINT{
		getPosition().x,
		space
	});
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