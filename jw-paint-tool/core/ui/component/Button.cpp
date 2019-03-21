#include "Button.h"

paint_tool::Button::Button(
	const	std::string					&id,
	const	POINT						&position,
	const	SIZE						&size,
	const	std::wstring				&text,
	const	std::string					&style_set_id,
	const	std::function<void(void)>	callback
) :
	ComponentGroup(id, position, style_set_id),
	callback(callback)
{
	
	/* make the label for this button */

	p_component_t label = std::make_unique<StaticLabel>(
		"btn_label",
		POINT{ 0, 0 },
		text,
		style_set_id,
		"default"
	);
	//addComponent(label);

	/* make the box for this button */

	p_component_t box = std::make_unique<StaticBox>(
		"btn_box",
		POINT { 0, 0 },
		size,
		style_set_id
	);
	addComponent(box);

	setDraggable(true);
}

paint_tool::Button::~Button() {
	//
}

void paint_tool::Button::onLeftMouseButtonUp(const POINT &mouse) {
	ComponentGroup::onLeftMouseButtonUp(mouse);

	if (wasHit(mouse))
		callback();
}