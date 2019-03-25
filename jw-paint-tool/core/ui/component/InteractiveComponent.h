#pragma once

#include "core\ui\component\Component.h"

//
// InteractiveComponent
//
// Extends the Component base class by offering interactive functionality.
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
		inline virtual void onLeftMouseUpLostHit();

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
			const	std::string	&id
		);

		InteractiveComponent(
			const	std::string	&id,
			const	SIZE		&size
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
		// The point where the left mouse down button was clicked, relative to
		// this Component.
		//
		// Used when dragging the Component so that the position doesn't jump
		// to the location of the mouse pointer.
		//
		POINT lmd_startpoint;
	};
}

void paint_tool::InteractiveComponent::onLeftMouseDownHit(const POINT &mouse) {

	/* this component was mouse down clicked on - make it active and reset focused */

	focused = false;
	active = true;
	lmd_startpoint = mouse;
}

void paint_tool::InteractiveComponent::onLeftMouseDownLostHit() {

	/* a new component was mouse down clicked on - reset focused and active to false */

	focused = false;
	active = false;
	lmd_startpoint = POINT{ -1,-1 };
}

void paint_tool::InteractiveComponent::onLeftMouseUpHit(const POINT &mouse) {

	/* this component was mouse up clicked on - make it focused, and reset active */

	focused = true;
	active = false;
	lmd_startpoint = POINT{ -1,-1 };
}

void paint_tool::InteractiveComponent::onLeftMouseUpLostHit() {

	/* a new component was mouse up clicked on - reset focused and active to false */

	focused = false;
	active = false;
}

void paint_tool::InteractiveComponent::onMouseMoveLostHit() {

	/* a new component was hovered over - reset hovered to false */

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