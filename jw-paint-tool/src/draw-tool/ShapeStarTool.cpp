#include "ShapeStarTool.h"

paint_tool::ShapeStarTool::ShapeStarTool(Drawing *drawing) :
	IDrawTool(drawing) {
	//
}

paint_tool::ShapeStarTool::~ShapeStarTool() {
	//
}

void paint_tool::ShapeStarTool::draw(const POINT & mouse) {

	Drawing *drawing = getDrawing();
	drawing->clearPoints();

	POINT relative_point = drawing->getRelativePoint(mouse);

	int num_points = 5;
	int segments = num_points * 2;
	double segment_angle = (2 * M_PI) / 10;
	double radius = (relative_point.x < relative_point.y ? relative_point.y : relative_point.x) / 2;
	
	for (int i = segments + 1; i >= 0; i--) {

		double r = radius * (double) ((i % 2 + 1) / 4.f);
		double angle = segment_angle * i;

		*drawing += POINT{
			(int) (r * sin(angle)),
			(int) (r * cos(angle))
		};
	}

	bool a = true;
}
