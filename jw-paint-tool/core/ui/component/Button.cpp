#include "Button.h"

paint_tool::Button::Button(
	const	std::string					&id,
	const	SIZE						&size,
	const	std::wstring				&text,
	const	std::string					&style_set_id,
	const	std::function<void(void)>	callback
) :
	ComponentGroup(id, style_set_id),
	callback(callback)
{

	/* make the box for this button */

	p_component_t box = std::make_unique<StaticBox>(
		"btn_box",
		size,
		style_set_id
		);
	addComponent(box);
	
	/* make the label for this button */

	p_component_t label = std::make_unique<StaticLabel>(
		"btn_label",
		text,
		style_set_id,
		"default"
	);
	Component *p_label = label.get();
	addComponent(label);

	/* must position the label after adding it - else, it won't have a parent */

	p_label->positionCenter();
	p_label->positionMiddle();
}

paint_tool::Button::~Button() {
	//
}

void paint_tool::Button::onLeftMouseButtonUp(const POINT &mouse) {
	ComponentGroup::onLeftMouseButtonUp(mouse);

	if (wasHit(mouse))
		callback();
}