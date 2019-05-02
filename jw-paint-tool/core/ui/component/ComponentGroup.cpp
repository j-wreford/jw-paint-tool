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

	/* get the first interactive child component whose hit test passes */

	InteractiveComponent *hit_component = getFirstHitInteractiveComponent(mouse);

	if (hit_component) {

		/* call onLeftMouseUpHit() on the hit child component */

		hit_component->onLeftMouseUpHit(
			hit_component->getRelativePoint(mouse)
		);
	}

	/* inform the component who passed the last left mouse up hit that it's lost it */

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

	/* handle dragging the last_mmh component first before attempting to
	   call onMouseMoveHit on a new component. this fixes cases where dragging a
	   component over another component, while the mouse was outside the
	   boundaries of the original component, would cancel the drag. */
	 
	if (lmouse_down && last_mmh && last_mmh->isDraggable()) {

		/* in the cases where the user is dragging a component, but the mouse
		   left the boundaries of it during dragging, we should still call
		   onMoveMoveHit on the component even though it wasn't. this fixes
		   cases where a very small component couldn't be dragged as the mouse
		   couldn't stay within the boundaries. */

		if (lmouse_down && last_mmh && last_mmh->isDraggable())
			last_mmh->onMouseMoveHit(
				last_mmh->getRelativePoint(mouse), lmouse_down
			);
	}

	/* there's not a component being dragged; get the first interactive child
	   component whose hit test passes */

	else if (InteractiveComponent *hit_component = getFirstHitInteractiveComponent(mouse)) {

		/* call onMouseMoveHit() on the hit child component */

		hit_component->onMouseMoveHit(
			hit_component->getRelativePoint(mouse), lmouse_down
		);

		/* call onMouseMoveLostHit on the last component to have onMouseMoveHit
			called upon it */

		if (last_mmh && last_mmh != hit_component)
			last_mmh->onMouseMoveLostHit();

		last_mmh = hit_component;
	}

	/* this component was mouse-moved over, but over no child components. we
	   still need to inform the last mouse moved hit child component that it's
	   lost its hover state. */

	else {

		if (last_mmh)
			last_mmh->onMouseMoveLostHit();

		last_mmh = nullptr;
	}
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
		getActiveComponent()->onChar(key, flags);
}

bool paint_tool::ComponentGroup::isInteractive() const {

	/* hidden components are never considered interactive. immediately return
	   false if this component group is hidden */

	if (isHidden())
		return false;

	/* for a component to be draggable, it must be interactive */

	if (isDraggable())
		return true;

	/* to get here, the component group is not yet considered interactive (but
	   it is not hidden). to be considered interactive, at least one of its
	   child components must be interactive. */

	auto it = std::find_if(components.begin(), components.end(),
		[](const p_component_t &component) {
			return component->isInteractive();
	});

	return it != components.end();
}

void paint_tool::ComponentGroup::addComponent(paint_tool::p_component_t &component) {

	component->setParent(this);

	components.push_back(std::move(component));

	recalculateSize();
}

void paint_tool::ComponentGroup::removeComponent(const std::string &id) {

	Component *removed = nullptr;

	components.remove_if([&id, &removed](const p_component_t &component) {

		if (component->getId() == id) {
			removed = component.get();
			return true;
		}
		return false;
	});

	if (last_lmdh == removed)
		last_lmdh = nullptr;

	if (last_lmuh == removed)
		last_lmuh = nullptr;

	if (last_mmh == removed)
		last_mmh = nullptr;
}

void paint_tool::ComponentGroup::addVerticalSpace(const int& height) {

	p_component_t v_space = std::make_unique<FixedSpace>(
		"fixed_space_" + std::to_string(components.size()),
		SIZE{ 1, height }
	);

	addComponent(v_space);
}

void paint_tool::ComponentGroup::addHorizontalSpace(const int& width) {

	p_component_t h_space = std::make_unique<FixedSpace>(
		"fixed_space_" + std::to_string(components.size()),
		SIZE{ width, 1 }
	);

	addComponent(h_space);
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

	/* update the origin */

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