#include "ComponentStyle.h"

paint_tool::ComponentStyle::ComponentStyle() {
	//
}

paint_tool::ComponentStyle::~ComponentStyle() {

	delete normal->text_colour;
	delete normal->bg_colour;
	delete normal->line_colour;
	delete normal->line_thickness;
	delete normal;

	delete active->text_colour;
	delete active->bg_colour;
	delete active->line_colour;
	delete active->line_thickness;
	delete active;

	delete focused->text_colour;
	delete focused->bg_colour;
	delete focused->line_colour;
	delete focused->line_thickness;
	delete focused;

	delete hovered->text_colour;
	delete hovered->bg_colour;
	delete hovered->line_colour;
	delete hovered->line_thickness;
	delete hovered;
}

paint_tool::ComponentStyle::StyleSet *paint_tool::ComponentStyle::getStyle(ComponentState state) {

	StyleSet *style_set = nullptr;
	
	switch (state) {

	case COMPONENT_STATE_NORMAL :
		style_set = normal;
		break;

	case COMPONENT_STATE_ACTIVE:
		style_set = active;
		break;

	case COMPONENT_STATE_FOCUSED:
		style_set = focused;
		break;

	case COMPONENT_STATE_HOVERED:
		style_set = hovered;
		break;
	}

	return style_set;
}