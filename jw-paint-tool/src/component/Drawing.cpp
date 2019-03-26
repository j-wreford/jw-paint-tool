#include "Drawing.h"

paint_tool::Drawing::Drawing(const std::string &id)	:
	InteractiveComponent(id) {
	//
}

paint_tool::Drawing::~Drawing() {

	for (POINT * point : points)
		delete point;
}

void paint_tool::Drawing::recalculateSize() {

	/* find the top-leftmost point */

	/* find the bottom-rightmost point */

}