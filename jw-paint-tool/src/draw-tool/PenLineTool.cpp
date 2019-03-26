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

	POINT relative_mouse = {
		mouse.x - drawing->getPosition().x - drawing->getOrigin().x,
		mouse.y - drawing->getPosition().y - drawing->getOrigin().y
	};

	*drawing = POINT{ 0, 0 };
	*drawing += relative_mouse;
}
