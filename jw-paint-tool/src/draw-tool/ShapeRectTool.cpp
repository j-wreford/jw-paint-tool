#include "ShapeRectTool.h"

paint_tool::ShapeRectTool::ShapeRectTool(Drawing *drawing) :
	IDrawTool(drawing) {
	//
}

paint_tool::ShapeRectTool::~ShapeRectTool() {
	//
}

void paint_tool::ShapeRectTool::draw(const POINT & mouse) {

	Drawing *drawing = getDrawing();

	POINT relative_point = drawing->getRelativePoint(mouse);

	*drawing = POINT{ 0, 0 };
	*drawing += POINT{ relative_point.x, 0 };
	*drawing += relative_point;
	*drawing += POINT{ 0, relative_point.y };
	*drawing += POINT{ 0, 0 };
}
