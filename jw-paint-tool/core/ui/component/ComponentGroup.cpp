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

		POINT position = getAbsolutePosition();
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

void paint_tool::ComponentGroup::onKeyDown(UINT key, UINT flags) {
	
	InteractiveComponent::onKeyDown(key, flags);

	if (getActiveComponent())
		getActiveComponent()->onKeyDown(key, flags);
}

void paint_tool::ComponentGroup::onChar(UINT key, UINT flags) {

	InteractiveComponent::onChar(key, flags);

	if (getActiveComponent())
		getActiveComponent()->onKeyDown(key, flags);
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

	/* calculate the union rect of all child components and grab the new
	   size from it */

	RECT rect = { 0, 0, 0, 0 };

	std::for_each(components.begin(), components.end(),
		[&rect](p_component_t &component) {

			RECT this_rect = component->getRect();

			::UnionRect(
				&rect,
				&rect,
				&this_rect
			);
	});

	SIZE new_size = {
		rect.right - rect.left,
		rect.bottom - rect.top
	};

	/* if the current rectangle is smaller than the minimum size, then increase
	   its dimensions */

	SIZE min_size = getMinimumSize();

	if (new_size.cx < min_size.cx)
		new_size.cx = min_size.cx;

	if (new_size.cy < min_size.cy)
		new_size.cy = min_size.cy;

	/* update the origin if the caculated union rect goes into the negative
	   coordinate space */

	POINT origin = getOrigin();
	POINT new_origin = origin;

	if (rect.left < 0)
		new_origin.x = -rect.left;

	if (rect.top < 0)
		new_origin.y = -rect.top;

	if (new_origin.x != origin.x ||
		new_origin.y != origin.y)
		setOrigin(new_origin, true);

	/* update the size */

	setSize(new_size);
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