#include "ComponentGroup.h"

paint_tool::ComponentGroup::ComponentGroup(
	const	std::string	&id,
	const	POINT		&position,
	const	std::string &style_set_id,
	const	bool		&fill_background
) :
	InteractiveComponent(id, position, style_set_id),
	focused_component(nullptr),
	active_component(nullptr),
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

void paint_tool::ComponentGroup::onLeftMouseButtonDown(const POINT &mouse) {
	InteractiveComponent::onLeftMouseButtonDown(mouse);

	/* 1. call onLeftMouseButtonDown on each interactive child component */

	for (auto &pair : components) {

		Component *component = pair.second.get();

		if (component->isInteractive()) {

			InteractiveComponent *inter_comp =
				dynamic_cast<InteractiveComponent *>(component);

			if (inter_comp)
				inter_comp->onLeftMouseButtonDown(
					getRelativePoint(mouse)
				);
		}
	}
	
	/* 2. find the child component which is now active (after responding to
	      onLeftMouseButtonDown */

	auto it = std::find_if(components.begin(), components.end(),
		[](auto &pair) -> bool {

			bool active = false;
			
			InteractiveComponent *component =
				dynamic_cast<InteractiveComponent *>(pair.second.get());

			if (component)
				active = component->isActive();
			
			return active;
		}
	);
	
	/* 3. set the active_component property */

	if (it != components.end())
		active_component = dynamic_cast<InteractiveComponent *>(it->second.get());
}

void paint_tool::ComponentGroup::onLeftMouseButtonUp(const POINT &mouse) {
	InteractiveComponent::onLeftMouseButtonUp(mouse);

	/* 1. call onLeftMouseButtonUp on each interactive child component */

	for (auto &pair : components) {

		Component *component = pair.second.get();

		if (component->isInteractive()) {

			InteractiveComponent *inter_comp =
				dynamic_cast<InteractiveComponent *>(component);

			if (inter_comp)
				inter_comp->onLeftMouseButtonUp(
					getRelativePoint(mouse)
				);
		}
	}

	/* 2. find the child component which is now focused (after responding to
	      onLeftMouseButtonUp) */

	auto it = std::find_if(components.begin(), components.end(),
		[](auto &pair) -> bool {

			bool focused = false;

			InteractiveComponent *component =
				dynamic_cast<InteractiveComponent *>(pair.second.get());

			if (component)
				focused = component->isFocused();

			return focused;
		}
	);

	/* 3. set the focused_component and active_component properties */

	if (it != components.end())
		focused_component = dynamic_cast<InteractiveComponent *>(it->second.get());

	active_component = nullptr;
}

void paint_tool::ComponentGroup::onMouseMove(const POINT &mouse, const bool &lmouse_down) {
	InteractiveComponent::onMouseMove(mouse, lmouse_down);
	
	/* call onMouseMove on each interactive child component */

	for (auto &pair : components) {

		Component *component = pair.second.get();

		if (component->isInteractive()) {

			InteractiveComponent *inter_comp =
				dynamic_cast<InteractiveComponent *>(component);

			if (inter_comp)
				inter_comp->onMouseMove(
					getRelativePoint(mouse),
					lmouse_down
				);
		}
	}
}


bool paint_tool::ComponentGroup::isInteractive() const {

	bool interactive = isDraggable();

	/* if this component group isn't draggable, test to see if any of the child
	   components are interactive. if at least one is, then return true */

	if (!interactive) {

		auto it = std::find_if(components.begin(), components.end(), [](auto &pair) {
			return pair.second->isInteractive();
		});

		if (it != components.end())
			interactive = true;
	}

	return interactive;
}

void paint_tool::ComponentGroup::addComponent(paint_tool::p_component_t &component) {

	component->setParent(this);

	components.insert(
		std::make_pair(component->getId(), std::move(component))
	);

	recalculateSize();
}

void paint_tool::ComponentGroup::recalculateSize() {

	RECT rect = getAbsoluteRect();

	std::for_each(components.begin(), components.end(), [&rect](auto &pair) {

		RECT this_rect = pair.second->getAbsoluteRect();

		::UnionRect(
			&rect,
			&rect,
			&this_rect
		);
	});

	setRect(rect);
}