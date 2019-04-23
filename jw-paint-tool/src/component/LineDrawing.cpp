#include "LineDrawing.h"

paint_tool::LineDrawing::LineDrawing(const std::string &id) :
	Drawing(id) {
	addProperty(DRAW_PROP_COL_LINE);
	addProperty(DRAW_PROP_LINE_THICKNESS);
}

paint_tool::LineDrawing::~LineDrawing() {
	//
}

void paint_tool::LineDrawing::drawComponent(EasyGraphics *ctx) const {

	// While testing, to make it obvious whats being drawn
	ctx->setPenColour(EasyGraphics::clDarkMagenta, 2);

	std::list<POINT *> points = getPoints();

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