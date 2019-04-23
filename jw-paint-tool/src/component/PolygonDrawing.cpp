#include "PolygonDrawing.h"

paint_tool::PolygonDrawing::PolygonDrawing(const std::string &id) :
	Drawing(id) {
	addProperty(DRAW_PROP_COL_FILL);
}

paint_tool::PolygonDrawing::~PolygonDrawing() {
	//
}

void paint_tool::PolygonDrawing::drawComponent(EasyGraphics *ctx) const {

	// While testing, to make it obvious whats being drawn
	ctx->setPenColour(EasyGraphics::clDarkMagenta, 2);

	std::list<POINT *> points = getPoints();

	if (points.size() > 0) {

		/* need a polygon draw method here! */

	}
}