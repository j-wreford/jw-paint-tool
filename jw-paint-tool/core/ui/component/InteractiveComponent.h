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
		// Performs a check to see if the given mouse point lays
		// inside the boundary of the Component.
		//
		// If the test passes, then onHitTestPassed is called.
		//
		// The result of the test is returned.
		//
		bool hitTest(const POINT &mouse);

		//
		// The operations to perform whenever a successful hitTest check occurs
		//
		virtual void onHitTestPassed(const POINT &mouse) = 0;

		//
		// The operations to perform whenever the mouse is moved
		//
		virtual void onMouseMove(const POINT &mouse);

		//
		// Sets draggable to the value given
		//
		inline void setDraggable(const bool &_draggable);

		//
		// Sets focused to true
		//
		inline void giveFocus();

		//
		// Sets focused to false
		//
		inline void takeFocus();

		//
		// Returns true; the InteractiveComponent is ... interactive (wow)
		//
		inline virtual bool isInteractive() const override;

		//
		// Returns true when the Component is the last component to be clicked
		//
		inline bool isFocused() const;

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

	private:

		//
		// True when the Component is the last component to be clicked
		//
		bool focused;

		//
		// When true, the Component will be moved around when the user
		// clicks-and-drags on the Component
		//
		bool draggable;
	};
}

void paint_tool::InteractiveComponent::setDraggable(const bool &_draggable) {
	draggable = _draggable;
}

void paint_tool::InteractiveComponent::giveFocus() {
	focused = true;
}

void paint_tool::InteractiveComponent::takeFocus() {
	focused = false;
}

bool paint_tool::InteractiveComponent::isInteractive() const {
	return true;
}

bool paint_tool::InteractiveComponent::isFocused() const {
	return focused;
}

bool paint_tool::InteractiveComponent::isDraggable() const {
	return draggable;
}