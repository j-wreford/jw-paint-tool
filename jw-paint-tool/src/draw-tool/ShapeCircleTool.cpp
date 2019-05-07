#include "ShapeCircleTool.h"

paint_tool::ShapeCircleTool::ShapeCircleTool(Drawing *drawing) :
	IDrawTool(drawing) {
	//
}

paint_tool::ShapeCircleTool::~ShapeCircleTool() {
	//
}

void paint_tool::ShapeCircleTool::draw(const POINT & mouse) {

	Drawing *drawing = getDrawing();

	POINT relative_point = drawing->getRelativePoint(mouse);

	*drawing = POINT{ 0, 0 };
	*drawing += POINT{ relative_point.x, relative_point.y };
}
