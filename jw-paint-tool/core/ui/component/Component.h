#pragma once

#include <string>

#include "EasyGraphics.h"

//
// Component
//
// The base class for all user interface components to inherit from.
//

namespace paint_tool {

	class Component {
	public:

		//
		// Draws the component to the given EasyGraphics context
		//
		virtual void drawComponent(EasyGraphics *ctx) const = 0;

		//
		// Returns the position of the Component.
		//
		// If parent is not a nullptr, then the POINT returned will be relative
		// to it.
		//
		POINT getPosition() const;

		//
		// Sets the pointer to the parent Component
		//
		inline void setParent(Component *_parent);

	protected:

		Component(
			const	std::string	&id,
			const	POINT		&position,
			const	int			&fg_colour = 0x000000,
			const	int			&bg_colour = 0xffffff
		);
		~Component();

	private:

		//
		// The string used to uniquely identify the Component 
		//
		std::string id;

		//
		// The upper-left POINT of the Component, relative to the position of
		// the parent Component.
		//
		// If parent is a nullptr, then this value is relative to the upper-left
		// pixel of the screen.
		//
		POINT position;

		//
		// A pointer to the parent of the Component.
		//
		// This will be a nullptr unless the Component has been added to a
		// ComponentGroup.
		//
		Component *parent;

		//
		// BGR colour values the Component can use when drawing
		//
		int fg_colour, bg_colour;
	};
}

void paint_tool::Component::setParent(Component *_parent) {
	parent = _parent;
}