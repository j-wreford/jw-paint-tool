#include "Drawing.h"

paint_tool::Drawing::Drawing(const std::string &id)	:
	InteractiveComponent(id) {
	//
}

paint_tool::Drawing::~Drawing() {

	for (POINT * point : points)
		delete point;
}

void paint_tool::Drawing::drawComponent(EasyGraphics *ctx) const {

	if (points.size() > 0) {

		POINT *last = points.front();

		auto start_position = points.begin();
		std::advance(start_position, 1);

		std::for_each(start_position, points.end(), [&last, &ctx](POINT *point) {

			ctx->drawLine(last->x, last->y, point->x, point->y);
			last = point;
		});
	}
}

void paint_tool::Drawing::recalculateSize() {

	setSize(SIZE{ 0,0 });
	RECT rect = getRect();

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

	/* need to update the nwe origin etc etc */

	setRect(rect);
}