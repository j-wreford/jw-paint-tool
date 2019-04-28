#pragma once

#include <list>
#include <algorithm>

#include "core\ui\component\InteractiveComponent.h"
#include "src\enum\DrawingPropertiesEnum.h"

//
// Drawing
//
// A Component which is made up of a series of point data.
//
// This Drawing class does not define the drawComponent method. This is left for
// concrete Drawing classes to provide, as the method of which a Drawing can be
// drawn differs.
//
// See LineDrawing and PolygonDrawing for more.
//

namespace paint_tool {

	class IDrawTool;

	class Drawing :
		public InteractiveComponent {
	public:

		~Drawing();

		//
		// Returns the DrawingProperties the Drawing has
		//
		inline std::vector<DrawingProperties> getProperties() const;

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
		// Finds the top-leftmost point and the bottom-rightmost point
		// to calculate its size with
		//
		virtual void recalculateSize();

		// remove getComponentType!!!!
		virtual std::string getComponentType() const { return ""; };

	protected:

		Drawing(const std::string &id);

		//
		// Returns the points property
		//
		inline std::list<POINT *> getPoints() const;

		//
		// Adds a drawing property to the DrawingProperties container
		//
		inline void addProperty(DrawingProperties property);

	private:

		//
		// The properties the Drawing has.
		//
		// The properties in this container dictate what controls are visible
		// when the drawing is selected.
		//
		// For example, if DRAW_PROP_COL_FILL is within the container, then
		// a control to edit the fill colour of the Drawing will appear within
		// the selected drawing group component.
		//
		std::vector<DrawingProperties> properties;

		//
		// The series of points to draw lines between
		//
		std::list<POINT *> points;

		//
		// Clears the POINT list. This method does not call recalculateSize
		//
		inline void clearPoints();
	};
}

std::vector<paint_tool::DrawingProperties> paint_tool::Drawing::getProperties() const {
	return properties;
}

const paint_tool::Drawing& paint_tool::Drawing::operator=(const POINT &point) {
	clearPoints();
	points.push_back(new POINT(point));
	recalculateSize();
	return *this;
}

const paint_tool::Drawing& paint_tool::Drawing::operator=(const std::list<POINT> &_points) {
	clearPoints();
	for (POINT point : _points)
		points.push_back(new POINT(point));
	recalculateSize();
	return *this;
}

const paint_tool::Drawing& paint_tool::Drawing::operator+=(const POINT &point) {
	points.push_back(new POINT(point));
	recalculateSize();
	return *this;
}

std::list<POINT *> paint_tool::Drawing::getPoints() const {
	return points;
}

void paint_tool::Drawing::addProperty(DrawingProperties property) {

	if (std::find(properties.begin(), properties.end(), property) == properties.end())
		properties.push_back(property);
}

void paint_tool::Drawing::clearPoints() {

	for (POINT *point : points)
		delete point;

	points.clear();
}