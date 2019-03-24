#pragma once

#include "core\ui\component\Component.h"

//
// InteractiveComponent
//
// Extends the Component base class by offering a hitTest and onHitTestPassed
// methods to provide interactive functionality.
//

namespace paint_tool {

	class InteractiveComponent :
		public Component {
	public:

		virtual ~InteractiveComponent();

		//
		// The operations to perform whenever the mouse button is clicked on
		// the, Component.
		//
		// The lost hit variant is called when a new Component has their
		// onLeftMouseDownHit() method called.
		//
		// It is the caller's responsibility to transform the mouse paramter
		// into one that's relative to this Component.
		//
		// Any derived Component that overrides this method must still call
		// these versions.
		//
		inline virtual void onLeftMouseDownHit(const POINT &mouse);
		inline virtual void onLeftMouseDownLostHit();

		//
		// The operations to perform whenever the mouse button is moved on
		// the Component.
		//
		// The lost hit variant is called when a new Component has their
		// onLeftMouseUpHit() method called.
		//
		// Any derived Component that overrides this method must still call
		// these versions.
		//
		inline virtual void onLeftMouseUpHit(const POINT &mouse);
		inline virtual void onleftMouseUpLostHit();

		//
		// The operations to perform whenever the mouse button is moved on
		// the Component.

		// The lost hit variant is called when a new Component has their
		// onMouseMoveHit() method called.
		//
		// It is the caller's responsibility to transform the mouse paramter
		// into one that's relative to this Component.
		//
		// Any derived Component that overrides this method must still call
		// these versions.
		//
		virtual void onMouseMoveHit(const POINT &mouse, const bool& lmouse_down);
		inline virtual void onMouseMoveLostHit();

		//
		// Sets draggable to true or false
		//
		inline void setDraggable(const bool &_draggable);

		//
		// Returns true; the InteractiveComponent is ... interactive (wow)
		//
		inline virtual bool isInteractive() const override;

		//
		// Returns focused
		//
		inline bool isFocused() const;

		//
		// Returns active
		//
		inline bool isActive() const;
#
		//
		// Returns hovered
		//
		inline bool isHovered() const;

		//
		// Returns true when the Component has been set to be draggable
		//
		inline bool isDraggable() const;

		//
		// Returns true when the given relative mouse point lays
		// within the boundaries of the Component
		//
		inline bool wasHit(const POINT &mouse) const;

		//
		// Transforms the given absolute POINT into one that's relative to the
		// boundaries of the Component
		//
		POINT getRelativePoint(const POINT &point) const;

	protected:

		InteractiveComponent(
			const	std::string	&id,
			const	std::string &style_set_id = "default"
		);

		InteractiveComponent(
			const	std::string	&id,
			const	SIZE		&size,
			const	std::string &style_set_id = "default"
		);

	private:

		//
		// True when a mouse up event occurs on the Component
		//
		bool focused;

		//
		// True when a mouse down event occurs on the Component
		//
		bool active;

		//
		// True when a mouse move event occurs on the Component
		//
		bool hovered;

		//
		// When true, the Component will be moved around when the user
		// clicks-and-drags on the Component
		//
		bool draggable;

		//
		// The offset of a left mouse-click so that
		// mouse point + lmouse_down_offset = position.
		//
		// Used when 'dragging' the Component so that the position doesn't jump
		// to the location of the mouse pointer.
		//
		POINT lmouse_down_offset;
	};
}

void paint_tool::InteractiveComponent::onLeftMouseDownHit(const POINT &mouse) {

	active = true;

	lmouse_down_offset = POINT{
		mouse.x - getPosition().x,
		mouse.y - getPosition().y
	};
}

void paint_tool::InteractiveComponent::onLeftMouseDownLostHit() {

	active = false;

	lmouse_down_offset = POINT{
		-1,
		-1
	};
}

void paint_tool::InteractiveComponent::onLeftMouseUpHit(const POINT &mouse) {
	focused = true;
}

void paint_tool::InteractiveComponent::onleftMouseUpLostHit() {
	focused = false;
}

void paint_tool::InteractiveComponent::onMouseMoveLostHit() {
	hovered = false;
}

void paint_tool::InteractiveComponent::setDraggable(const bool &_draggable) {
	draggable = _draggable;
}

bool paint_tool::InteractiveComponent::isInteractive() const {
	return true;
}

bool paint_tool::InteractiveComponent::isFocused() const {
	return focused;
}

bool paint_tool::InteractiveComponent::isActive() const {
	return active;
}

bool paint_tool::InteractiveComponent::isHovered() const {
	return hovered;
}

bool paint_tool::InteractiveComponent::isDraggable() const {
	return draggable;
}

bool paint_tool::InteractiveComponent::wasHit(const POINT &mouse) const {
	return ::PtInRect(&getRect(), mouse);
}