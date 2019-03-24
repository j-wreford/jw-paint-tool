#include "ComponentStyle.h"

paint_tool::ComponentStyle::ComponentStyle() {
	//
}

paint_tool::ComponentStyle::~ComponentStyle() {

	delete normal;
	delete active;
	delete focused;
	delete hovered;
}

paint_tool::ComponentStyle::StyleSet *paint_tool::ComponentStyle::getStyleSet(ComponentState state) {

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

void paint_tool::ComponentStyle::setStyleSet(StyleSet *style_set, ComponentState state) {

	switch (state) {

	case COMPONENT_STATE_NORMAL:
		delete normal;
		normal = style_set;
		break;

	case COMPONENT_STATE_ACTIVE:
		delete active;
		active = style_set;
		break;

	case COMPONENT_STATE_FOCUSED:
		delete focused;
		focused = style_set;
		break;

	case COMPONENT_STATE_HOVERED:
		delete hovered;
		hovered = style_set;
		break;
	}
}
