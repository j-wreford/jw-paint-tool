#include "Drawing.h"

paint_tool::Drawing::Drawing(const std::string &id)	:
	InteractiveComponent(id) {
	addProperty(DRAW_PROP_MOVE);
	addProperty(DRAW_PROP_DEL);
}

paint_tool::Drawing::~Drawing() {

	for (POINT *point : points)
		delete point;
}

void paint_tool::Drawing::recalculateSize() {

	RECT rect = { 0, 0, 0, 0 };

	for (POINT *point : points) {

		if (point->x < rect.left)
			rect.left = point->x;
		else if (point->x > rect.right)
			rect.right = point->x;

		if (point->y < rect.top)
			rect.top = point->y;
		else if (point->y > rect.bottom)
			rect.bottom = point->y;
	}

	setOrigin(POINT{
		-rect.left,
		-rect.top
	}, true);

	setSize(SIZE{
		rect.right - rect.left,
		rect.bottom - rect.top
	});
}