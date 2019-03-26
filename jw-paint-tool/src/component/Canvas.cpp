#include "Canvas.h"

paint_tool::Canvas::Canvas(const std::string &id) :
	ComponentGroup(id),
	draw_tool(nullptr) {
	//
}

paint_tool::Canvas::~Canvas() {
	//
}

void paint_tool::Canvas::drawComponent(EasyGraphics *ctx) const {

	ComponentGroup::drawComponent(ctx);

	RECT rect = getAbsoluteRect();

	const int square = 15;

	/* just for this canvas component, ignore the whole styleset system
	   and set the colours here */

	const int col = 0xf7f7f7;
	ctx->selectBackColour(col);
	ctx->setPenColour(col, 1);

	for (int i = rect.top; i < rect.bottom; i += square) {

		for (int j = rect.left; j < rect.right; j += square) {

			if (((j + i) % 2) == 1)
				ctx->drawRectangle(j, i, square, square, true);
		}
	}
}

void paint_tool::Canvas::onLeftMouseDownHit(const POINT &mouse) {
	
	p_component_t drawing = std::make_unique<Drawing>(
		"drawing_" + std::to_string(getChildComponents()->size())
	);

	Drawing *p_drawing = dynamic_cast<Drawing *>(drawing.get());
	addComponent(drawing);

	/* for now, just use a pen line tool for testing purposes */
	
	draw_tool = new PenLineTool(p_drawing, mouse);
}

void paint_tool::Canvas::onLeftMouseUpHit(const POINT &mouse) {

	if (draw_tool)
		delete draw_tool;
}

void paint_tool::Canvas::onMouseMoveHit(const POINT &mouse, const bool& lmouse_down) {

	if (draw_tool && lmouse_down && hasState(COMPONENT_STATE_ACTIVE))
		draw_tool->draw(mouse);
}