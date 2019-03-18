#include "ComponentGroup.h"

paint_tool::ComponentGroup::ComponentGroup(
	const	std::string	&id,
	const	POINT		&position,
	const	std::string &style_set_id,
	const	bool		&fill_background
) :
	InteractiveComponent(id, position, style_set_id),
	focused_component(nullptr),
	fill_background(fill_background) {
	
	recalculateSize();
}

paint_tool::ComponentGroup::~ComponentGroup() {
	//
}

void paint_tool::ComponentGroup::drawComponent(EasyGraphics *ctx) const {

	if (fill_background) {

		POINT position = getPosition();
		SIZE size = getSize();

		ctx->drawRectangle(position.x, position.y, size.cx, size.cy, true);
	}
}

void paint_tool::ComponentGroup::onHitTestPassed(const POINT &mouse) {

	if (focused_component)
		focused_component->takeFocus();
	
	if (isInteractive()) {

		auto it = std::find_if(child_components.begin(), child_components.end(), [](auto &pair) {
			return pair.second->isInteractive();
		});

		if (it != child_components.end()) {

			InteractiveComponent *component =
				dynamic_cast<InteractiveComponent *>(it->second.get());

			if (component) {

				component->hitTest(mouse);

				component->giveFocus();
				focused_component = component;
			}
		}
	}
}

bool paint_tool::ComponentGroup::isInteractive() const {

	bool interactive = isDraggable();

	/* if this component group isn't draggable, test to see if any of the child
	   components are interactive. if at least one is, then return true */

	if (!interactive) {

		auto it = std::find_if(child_components.begin(), child_components.end(), [](auto &pair) {
			return pair.second->isInteractive();
		});

		if (it != child_components.end())
			interactive = true;
	}

	return interactive;
}

void paint_tool::ComponentGroup::addComponent(paint_tool::p_component_t &component) {

	component->setParent(this);

	child_components.insert(
		std::make_pair(component->getId(), std::move(component))
	);

	recalculateSize();
}

void paint_tool::ComponentGroup::recalculateSize() {

	RECT rect = getAbsoluteRect();

	std::for_each(child_components.begin(), child_components.end(), [&rect](auto &pair) {

		RECT this_rect = pair.second->getAbsoluteRect();

		::UnionRect(
			&rect,
			&rect,
			&this_rect
		);
	});

	setRect(rect);
}