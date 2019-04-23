#include "MoveTool.h"

paint_tool::MoveTool::MoveTool(Drawing *drawing) :
	IDrawTool(drawing) {
	//
}

paint_tool::MoveTool::~MoveTool() {
	//
}

void paint_tool::MoveTool::draw(const POINT & mouse) {

	Drawing *drawing = getDrawing();

	drawing->setPosition(drawing->getRelativePoint(mouse));
}
