#include "Drawing.h"

paint_tool::Drawing::Drawing(const std::string &id)	:
	InteractiveComponent(id) {
	//
}

paint_tool::Drawing::~Drawing() {

	for (POINT *point : points)
		delete point;
}

void paint_tool::Drawing::drawComponent(EasyGraphics *ctx) const {

	// While testing, to make it obvious whats being drawn
	ctx->setPenColour(EasyGraphics::clDarkMagenta, 2);

	if (points.size() > 0) {

		POINT pos = getAbsolutePosition();
		POINT origin = getOrigin();

		/* add the position of the drawing to the point, so that
		   it's drawn in the correct space in the window */

		POINT last = {
			points.front()->x + pos.x + origin.x,
			points.front()->y + pos.y + origin.y
		};

		auto start_position = points.begin();
		std::advance(start_position, 1);

		std::for_each(start_position, points.end(), [&pos, &origin, &last, &ctx](POINT *point) {

			/* add the position of the drawing to the point, so that
			   it's drawn in the correct space in the window */

			POINT next = {
				point->x + pos.x + origin.x,
				point->y + pos.y + origin.y
			};

			ctx->drawLine(last.x, last.y, next.x, next.y);
			last = next;
		});
	}
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