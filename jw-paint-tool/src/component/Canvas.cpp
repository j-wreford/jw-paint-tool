#include "Canvas.h"

paint_tool::Canvas::Canvas(const std::string &id) :
	ComponentGroup(id) {
	//
}

paint_tool::Canvas::~Canvas() {
	//
}

void paint_tool::Canvas::drawComponent(EasyGraphics *ctx) {

	ComponentGroup::drawComponent(ctx);

	POINT pos = getAbsolutePosition();
	SIZE size = getSize();

	const int square = 25;
	const int even_col = 0xffffff;
	const int odd_col = 0xf7f7f7;

	for (int i = pos.y; i < size.cy; i++) {

		for (int j = pos.x; j < size.cx; j++) {

			ctx->selectBackColour(((j + i) % 2) == 1 ? even_col : odd_col);
			ctx->drawRectangle(j, i, square, square, true);
		}
	}
}