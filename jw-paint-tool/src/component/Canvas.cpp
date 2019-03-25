#include "Canvas.h"

paint_tool::Canvas::Canvas(const std::string &id) :
	ComponentGroup(id) {
	


}

paint_tool::Canvas::~Canvas() {
	//
}

void paint_tool::Canvas::drawComponent(EasyGraphics *ctx) const {

	ComponentGroup::drawComponent(ctx);

	RECT rect = getAbsoluteRect();

	const int square = 15;
	const int even_col = 0xffffff;
	const int odd_col = 0xf7f7f7;

	for (int i = rect.top; i < rect.bottom; i += square) {

		for (int j = rect.left; j < rect.right; j += square) {

			/* just for this canvas component, ignore the whole styleset system
			   and set the colours here */

			int colour = ((j + i) % 2) == 1 ? even_col : odd_col;
			ctx->selectBackColour(colour);
			ctx->setPenColour(colour, 1);

			ctx->drawRectangle(j, i, square, square, true);
		}
	}
}