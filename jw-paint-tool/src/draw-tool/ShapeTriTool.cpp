#include "ShapeTriTool.h"

paint_tool::ShapeTriTool::ShapeTriTool(Drawing *drawing) :
	IDrawTool(drawing) {
	//
}

paint_tool::ShapeTriTool::~ShapeTriTool() {
	//
}

void paint_tool::ShapeTriTool::draw(const POINT & mouse) {

	Drawing *drawing = getDrawing();

	POINT relative_point = drawing->getRelativePoint(mouse);

	*drawing = POINT{ (relative_point.x / 2), 0 };
	*drawing += POINT{ relative_point.x, relative_point.y };
	*drawing += POINT{ 0, relative_point.y };
	*drawing += POINT{ (relative_point.x / 2), 0 };
}
