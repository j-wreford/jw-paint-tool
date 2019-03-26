#pragma once

#include <list>

#include "core\ui\component\InteractiveComponent.h"

//
// Drawing
//
// A component which is made up of a series of point data.
//

namespace paint_tool {

	class IDrawTool;

	class Drawing :
		public InteractiveComponent {
	public:

		//
		// Only a drawing tool should be able to manipulate point data
		//
		friend class IDrawTool;

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

		//
		// Clears the POINT list and adds point to it
		//
		inline const Drawing& operator=(const POINT &point);

		//
		// Clears the POINT list and adds the given points list to it
		//
		inline const Drawing& operator=(const std::list<POINT> &points);

		//
		// Adds the given point to the POINT list
		//
		inline const Drawing& operator+=(const POINT &point);

		//
		// Clears the POINT list
		//
		inline void clearPoints();
	};
}

inline const paint_tool::Drawing& paint_tool::Drawing::operator=(const POINT &point) {
	clearPoints();
	points.push_back(new POINT(point));
}

inline const paint_tool::Drawing& paint_tool::Drawing::operator=(const std::list<POINT> &_points) {
	clearPoints();
	for (POINT point : _points)
		points.push_back(new POINT(point));
}

inline const paint_tool::Drawing& paint_tool::Drawing::operator+=(const POINT &point) {
	points.push_back(new POINT(point));
}

void paint_tool::Drawing::clearPoints() {
	points.clear();
}