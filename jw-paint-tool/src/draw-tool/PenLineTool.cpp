#include "PenLineTool.h"

paint_tool::PenLineTool::PenLineTool(Drawing *drawing) :
	IDrawTool(drawing) {
	//
}

paint_tool::PenLineTool::~PenLineTool() {
	//
}

void paint_tool::PenLineTool::draw(const POINT & mouse) {

	Drawing *drawing = getDrawing();

	*drawing = POINT{ 0, 0 };
	*drawing += drawing->getRelativePoint(mouse);
}
