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

	if (points.size() > 3) {

		POINT pos = getAbsolutePosition();
		POINT origin = getOrigin();

		/* convert the std::list container to a POINT array */

		POINT *points_arr = new POINT[points.size()];

		int i = 0;

		std::for_each(points.begin(), points.end(), [&](POINT *p) {
			points_arr[i++] = POINT{
				p->x + pos.x + origin.x,
				p->y + pos.y + origin.y
			};
		});

		ctx->drawPolygon(points_arr, points.size(), true);

		delete[] points_arr;
	}
}