#include "DrawingFactory.h"

paint_tool::DrawingFactory::DrawingFactory() : count(0) {
	//
}

paint_tool::DrawingFactory::~DrawingFactory() {
	//
}

paint_tool::p_component_t paint_tool::DrawingFactory::makeDrawing(
	const	std::string					&type,
	const	POINT						&pos,
	const	ComponentStyle::StyleSet	&style_set,
	const	std::list<POINT *>			&points
) {

	p_component_t drawing = nullptr;

	std::string id = "drawing_" + std::to_string(count++);

	if (type == "polygon")
		drawing = std::make_unique<PolygonDrawing>(id);

	if (type == "line")
		drawing = std::make_unique<LineDrawing>(id);

	if (Drawing *p_drawing = dynamic_cast<Drawing *>(drawing.get())) {

		p_drawing->setPosition(pos);

		if (style_set.bg_colour)
			p_drawing->setBgColour(*style_set.bg_colour);

		if (style_set.line_colour)
			p_drawing->setLineColour(*style_set.line_colour);

		if (style_set.line_thickness)
			p_drawing->setLineThickness(*style_set.line_thickness);

		*p_drawing = points;
	}

	return drawing;
}