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
		// The operations to perform on the Component whenever the the left
		// mouse button is pressed.
		//
		// It is the caller's responsibility to transform the mouse paramter
		// into one that's relative to this Component.
		//
		// If overriding this method, the method must still
		// call InteractiveComponent's version.
		//
		virtual void onLeftMouseButtonDown(const POINT &mouse);

		//
		// The operations to perform on the Component whenever the left mouse
		// button is released.
		//
		// It is the caller's responsibility to transform the mouse paramter
		// into one that's relative to this Component.
		//
		// If overriding this method, the method must still
		// call InteractiveComponent's version.
		//
		virtual void onLeftMouseButtonUp(const POINT &mouse);

		//
		// The operations to perform on the Component whenever the mouse is
		// moved.
		//
		// It is the caller's responsibility to transform the mouse paramter
		// into one that's relative to this Component.
		//
		// If overriding this method, the method must still
		// call InteractiveComponent's version.
		//
		virtual void onMouseMove(const POINT &mouse, const bool& lmouse_down);

		//
		// Sets draggable to the value given
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

		//
		// Returns true when the Component has been set to be draggable
		//
		inline bool isDraggable() const;

	protected:

		InteractiveComponent(
			const	std::string	&id,
			const	POINT		&position,
			const	std::string &style_set_id = "default"
		);

		InteractiveComponent(
			const	std::string	&id,
			const	POINT		&position,
			const	SIZE		&size,
			const	std::string &style_set_id = "default"
		);

		//
		// Performs a check to see if the given mouse point lays
		// inside the boundary of the Component.
		//
		// The result of the test is returned.
		//
		inline bool wasHit(const POINT &mouse) const;

		//
		// Transforms the given absolute POINT into one that's relative to the
		// boundaries of the Component
		//
		POINT getRelativePoint(const POINT &point) const;

	private:

		//
		// Trrue when a mouse up event occurs and it was within the the
		// Component's boundaries
		//
		bool focused;

		//
		// True when starting from a mouse down event that occured within
		// the Component's boundaries, up until a mouse up event occurs.
		//
		// I.e, the Component is active when the mouse is being press-and-held
		// over it.
		//
		bool active;

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

bool paint_tool::InteractiveComponent::isDraggable() const {
	return draggable;
}

bool paint_tool::InteractiveComponent::wasHit(const POINT &mouse) const {
	return ::PtInRect(&getRect(), mouse);
}