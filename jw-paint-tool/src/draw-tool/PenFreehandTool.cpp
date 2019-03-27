#include "PenFreehandTool.h"

paint_tool::PenFreehandTool::PenFreehandTool(Drawing *drawing) :
	IDrawTool(drawing) {
	*drawing = POINT{ 0, 0 };
}

paint_tool::PenFreehandTool::~PenFreehandTool() {
	//
}

void paint_tool::PenFreehandTool::draw(const POINT & mouse) {

	Drawing *drawing = getDrawing();
	*drawing += drawing->getRelativePoint(mouse);
}
