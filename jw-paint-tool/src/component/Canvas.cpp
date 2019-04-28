#include "Canvas.h"

paint_tool::Canvas::Canvas(const std::string &id) :
	ComponentGroup(id),
	draw_tool(nullptr) {
	//
}

paint_tool::Canvas::~Canvas() {
	
	if (draw_tool)
		delete draw_tool;
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

	ComponentGroup::onLeftMouseDownHit(mouse);

	/* if the current drawing tool selection is anything but a management tool,
	   then create a new Drawing component and pass it to the drawing tool
	   object */

	if (AppData::getInstance()->getToolChoice() != TOOL_MOVE &&
		AppData::getInstance()->getToolChoice() != TOOL_DEL) {

		/* figure out which sort of drawing object we need */

		/* TODO: Offload creation of the drawing component to the draw tools.
		   add a getter method to std::move the Draw to the Canvas */

		p_component_t drawing;

		if (AppData::getInstance()->getToolChoice() == TOOL_PEN_FREEHAND ||
			AppData::getInstance()->getToolChoice() == TOOL_PEN_LINE) {
			drawing = std::make_unique<LineDrawing>(
				"drawing_" + std::to_string(getChildComponents()->size())
			);
		}

		else {
			drawing = std::make_unique<PolygonDrawing>(
				"drawing_" + std::to_string(getChildComponents()->size())
			);
		}

		drawing->setPosition(mouse);

		Drawing *p_drawing = dynamic_cast<Drawing *>(drawing.get());
		addComponent(drawing);

		switch (AppData::getInstance()->getToolChoice()) {

		case TOOL_MOVE:
			//
			break;

		case TOOL_DEL:
			//
			break;

		case TOOL_PEN_FREEHAND:
			draw_tool = new PenFreehandTool(p_drawing);
			break;

		case TOOL_PEN_LINE:
			draw_tool = new PenLineTool(p_drawing);
			break;

		case TOOL_SHAPE_RECT:
			draw_tool = new ShapeRectTool(p_drawing);
			break;

		default:
			draw_tool = new PenFreehandTool(p_drawing);
		}
	}

	/* else, either move or delete the Drawing component that was just
	   selected */

	else {

		AppData::getInstance()->setDrawingChoice(dynamic_cast<Drawing *>(getActiveComponent()));

		if (AppData::getInstance()->getToolChoice() == TOOL_MOVE)
			bool a = true;
		
		if (AppData::getInstance()->getToolChoice() == TOOL_DEL)
			bool a = true;
	}
}

void paint_tool::Canvas::onLeftMouseUpHit(const POINT &mouse) {

	ComponentGroup::onLeftMouseUpHit(mouse);

	if (draw_tool) {

		/* select the finished drawing */

		Component *last = getChildComponents()->back().get();
		AppData::getInstance()->setDrawingChoice(dynamic_cast<Drawing *>(last));

		/* clean up the draw tool */

		delete draw_tool;
		draw_tool = nullptr;
	}
}

void paint_tool::Canvas::onMouseMoveHit(const POINT &mouse, const bool& lmouse_down) {

	ComponentGroup::onMouseMoveHit(mouse, lmouse_down);

	if (draw_tool && hasState(COMPONENT_STATE_ACTIVE))
		draw_tool->draw(mouse);
}