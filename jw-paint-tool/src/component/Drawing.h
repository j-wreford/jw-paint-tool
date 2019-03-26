#pragma once

#include <list>
#include <algorithm>

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

		Drawing(const std::string &id);
		~Drawing();

		//
		// Draws lines between all its points
		//
		virtual void drawComponent(EasyGraphics *ctx) const override;

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

		//
		// Finds the top-leftmost point and the bottom-rightmost point
		// to calculate its size with
		//
		virtual void recalculateSize();

		// remove getComponentType!!!!
		virtual std::string getComponentType() const { return ""; };

	private:

		//
		// The series of points to draw lines between
		//
		std::list<POINT *> points;
	};
}

inline const paint_tool::Drawing& paint_tool::Drawing::operator=(const POINT &point) {
	clearPoints();
	points.push_back(new POINT(point));
	return *this;
}

inline const paint_tool::Drawing& paint_tool::Drawing::operator=(const std::list<POINT> &_points) {
	clearPoints();
	for (POINT point : _points)
		points.push_back(new POINT(point));
	return *this;
}

inline const paint_tool::Drawing& paint_tool::Drawing::operator+=(const POINT &point) {
	points.push_back(new POINT(point));
	return *this;
}

void paint_tool::Drawing::clearPoints() {
	points.clear();
}