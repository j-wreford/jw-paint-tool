#include "CircleDrawing.h"

paint_tool::CircleDrawing::CircleDrawing(const std::string &id) :
	Drawing(id) {
	addProperty(DRAW_PROP_COL_LINE);
	addProperty(DRAW_PROP_LINE_THICKNESS);
}

paint_tool::CircleDrawing::~CircleDrawing() {
	//
}

void paint_tool::CircleDrawing::drawComponent(EasyGraphics *ctx) const {

	std::list<POINT *> points = getPoints();

	if (points.size() == 2) {

		POINT pos = getAbsolutePosition();
		POINT origin = getOrigin();

		POINT *center = points.front();
		POINT *radius = *std::next(points.begin());

		ctx->drawCircle(center->x + pos.x + origin.x, center->y + pos.y + origin.y, (radius->x - center->x), true);
	}
}