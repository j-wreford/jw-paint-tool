#include "ComponentGroup.h"

paint_tool::ComponentGroup::ComponentGroup(
	const	std::string	&id,
	const	bool		&fill_background
) :
	InteractiveComponent(id),
	layout(LAYOUT_MANUAL),
	last_lmdh(nullptr),
	last_lmuh(nullptr),
	last_mmh(nullptr),
	minimum_size(SIZE{ 0,0 }),
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

void paint_tool::ComponentGroup::onLeftMouseDownHit(const POINT &mouse) {

	InteractiveComponent::onLeftMouseDownHit(mouse);

	/* 1. get the first interactive child component whose hit test passes */

	InteractiveComponent *hit_component = getFirstHitInteractiveComponent(mouse);

	if (hit_component) {

		/* 2.1 call onLeftMouseDownHit() on the hit child component */

		hit_component->onLeftMouseDownHit(
			hit_component->getRelativePoint(mouse)
		);
	}

	if (last_lmdh && last_lmdh != hit_component)
		last_lmdh->onLeftMouseDownLostHit();

	last_lmdh = hit_component;
}

void paint_tool::ComponentGroup::onLeftMouseDownLostHit() {

	InteractiveComponent::onLeftMouseDownLostHit();

	if (last_lmdh)
		last_lmdh->onLeftMouseDownLostHit();

	last_lmdh = nullptr;
}

void paint_tool::ComponentGroup::onLeftMouseUpHit(const POINT &mouse) {

	InteractiveComponent::onLeftMouseUpHit(mouse);

	/* 1. get the first interactive child component whose hit test passes */

	InteractiveComponent *hit_component = getFirstHitInteractiveComponent(mouse);

	if (hit_component) {

		/* 2.1 call onLeftMouseUpHit() on the hit child component */

		hit_component->onLeftMouseUpHit(
			hit_component->getRelativePoint(mouse)
		);
	}
#
	if (last_lmuh && last_lmuh != hit_component)
		last_lmuh->onLeftMouseUpLostHit();

	last_lmuh = hit_component;
}

void paint_tool::ComponentGroup::onLeftMouseUpLostHit() {

	InteractiveComponent::onLeftMouseUpLostHit();

	if (last_lmuh)
		last_lmuh->onLeftMouseUpLostHit();

	last_lmuh = nullptr;
}

void paint_tool::ComponentGroup::onMouseMoveHit(const POINT &mouse, const bool &lmouse_down) {

	InteractiveComponent::onMouseMoveHit(mouse, lmouse_down);

	/* 1. get the first interactive child component whose hit test passes */

	InteractiveComponent *hit_component = getFirstHitInteractiveComponent(mouse);

	if (hit_component) {

		/* 2.1 call onMouseMoveHit() on the hit child component */

		hit_component->onMouseMoveHit(
			hit_component->getRelativePoint(mouse), lmouse_down
		);
	}

	if (last_mmh && last_mmh != hit_component)
		last_mmh->onMouseMoveLostHit();

	last_mmh = hit_component;
}

void paint_tool::ComponentGroup::onMouseMoveLostHit() {

	InteractiveComponent::onMouseMoveLostHit();

	if (last_mmh)
		last_mmh->onMouseMoveLostHit();

	last_mmh = nullptr;
}

bool paint_tool::ComponentGroup::isInteractive() const {

	bool interactive = isDraggable();

	/* if this component group isn't draggable, test to see if any of the child
	   components are interactive. if at least one is, then return true */

	if (!interactive) {

		auto it = std::find_if(components.begin(), components.end(),
			[](const p_component_t &component) {
				return component->isInteractive();
		});

		interactive = (it != components.end());
	}

	return interactive;
}

void paint_tool::ComponentGroup::addComponent(paint_tool::p_component_t &component) {

	component->setParent(this);

	components.push_back(std::move(component));

	recalculateSize();
}

void paint_tool::ComponentGroup::addVerticalSpace(const int& height) {

	components.push_back(
		std::make_unique<FixedSpace>(
			"fixed_space_" + std::to_string(components.size()),
			SIZE{ 0, height }
		)
	);
}

void paint_tool::ComponentGroup::addHorizontalSpace(const int& width) {

	components.push_back(
		std::make_unique<FixedSpace>(
			"fixed_space_" + std::to_string(components.size()),
			SIZE{ width, 0 }
		)
	);
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
	std::for_each(components.begin(), components.end(),
		[&rect](p_component_t &component) {

			RECT this_rect = component->getRect();

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

	/* if the current rectangle is smaller than the minimum size, then increase
	   its dimensions */

	SIZE min_size = getMinimumSize();

	if ((rect.right - rect.left) < min_size.cx)
		rect.right = rect.left + min_size.cx;

	if ((rect.bottom - rect.top) < min_size.cy)
		rect.bottom = rect.top + min_size.cy;

	/* adjust the position to make it appear that component's haven't moved
	   if the origin has changed */

	pos.x -= origin.x;
	pos.y -= origin.y;

	/* update properties */

	setOrigin(origin);
	setRect(rect);
	setPosition(pos);
}

paint_tool::InteractiveComponent *paint_tool::ComponentGroup::getFirstHitInteractiveComponent(const POINT &mouse) {
	
	auto it = std::find_if(components.begin(), components.end(),
		[&mouse](p_component_t &component) -> bool {

		if (component->isInteractive()) {

			InteractiveComponent *interactive =
				dynamic_cast<InteractiveComponent *>(component.get());

			if (interactive)
				return interactive->wasHit(mouse);
		}

		return false;
	});

	return (it == components.end() ? nullptr : dynamic_cast<InteractiveComponent *>(it->get()));
}
