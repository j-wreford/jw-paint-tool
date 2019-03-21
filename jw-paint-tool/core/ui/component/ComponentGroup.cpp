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
	last_active_component(nullptr),
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

	if (active_component)
		last_active_component = active_component;

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

	POINT pos = getPosition();
	POINT origin = getOrigin();

	/* get the position of the point where the origin lies */

	pos.x += origin.x;
	pos.y += origin.y;

	/* reset the size to 0 x 0 so it can shrink from its previous size */

	setSize(SIZE{ 0, 0 });

	/* calculate the union rect of all child components */

	RECT rect = getRect();
	std::for_each(components.begin(), components.end(), [&rect](auto &pair) {

		RECT this_rect = pair.second->getRect();

		::UnionRect(
			&rect,
			&rect,
			&this_rect
		);
	});

	/* union rect does not consider the fact that a child component's position
	   might be at [10,10]. we need to include the leading space in the group's
	   rectangle */

	if (rect.left > 0)
		rect.left = 0;
	else
		origin.x = -rect.left;

	if (rect.top > 0)
		rect.top = 0;
	else
		origin.y = -rect.top;

	/* adjust the position to make it appear that the bottom-right point of the
	   group's border hasn't moved */

	pos.x -= origin.x;
	pos.y -= origin.y;

	/* update properties */

	setOrigin(origin);
	setRect(rect);
	setPosition(pos);
}