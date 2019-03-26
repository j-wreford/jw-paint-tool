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

	// While testing, to make it obvious whats being drawn
	ctx->setPenColour(EasyGraphics::clDarkMagenta, 2);

	if (points.size() > 0) {

		POINT pos = getAbsolutePosition();

		POINT last = {
			points.front()->x += pos.x,
			points.front()->y += pos.y
		};

		auto start_position = points.begin();
		std::advance(start_position, 1);

		std::for_each(start_position, points.end(), [&pos, &last, &ctx](POINT *point) {

			POINT next = {
				point->x += pos.x,
				point->y += pos.y
			};

			ctx->drawLine(last.x, last.y, next.x, next.y);
			last = next;
		});
	}
}

void paint_tool::Drawing::recalculateSize() {
	/*
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

	/* need to update the nwe origin etc etc

	setRect(rect);*/
}