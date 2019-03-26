#pragma once

#include <list>

#include "core\ui\component\InteractiveComponent.h"

//
// Drawing
//
// A component which is made up of a series of point data.
//

namespace paint_tool {

	class Drawing :
		public InteractiveComponent {
	public:

		Drawing(const std::string &id);
		~Drawing();

		//
		// Finds the top-leftmost point and the bottom-rightmost point
		// to calculate its size with
		//
		virtual void recalculateSize();

	private:

		//
		// The series of points to draw lines between
		//
		std::list<POINT *> points;
	};
}