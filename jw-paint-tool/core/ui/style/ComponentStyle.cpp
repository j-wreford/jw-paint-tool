#include "ComponentStyle.h"

paint_tool::ComponentStyle::ComponentStyle() {
	//
}

paint_tool::ComponentStyle::~ComponentStyle() {
	//
}

const paint_tool::ComponentStyle::StyleSet *paint_tool::ComponentStyle::getStyleSet(ComponentState state) const {

	StyleSet *style_set = nullptr;
	
	switch (state) {

	case COMPONENT_STATE_NORMAL :
		style_set = normal.get();
		break;

	case COMPONENT_STATE_ACTIVE:
		style_set = active.get();
		break;

	case COMPONENT_STATE_FOCUSED:
		style_set = focused.get();
		break;

	case COMPONENT_STATE_HOVERED:
		style_set = hovered.get();
		break;
	}

	return style_set;
}

paint_tool::ComponentStyle::StyleSet *paint_tool::ComponentStyle::getStyleSet(ComponentState state) {
	return const_cast<ComponentStyle::StyleSet *>(const_cast<const ComponentStyle *>(this)->getStyleSet(state));
}

void paint_tool::ComponentStyle::setStyleSet(StyleSet *style_set, ComponentState state) {

	switch (state) {

	case COMPONENT_STATE_NORMAL:
		normal = std::unique_ptr<StyleSet>(style_set);
		break;

	case COMPONENT_STATE_ACTIVE:
		active = std::unique_ptr<StyleSet>(style_set);
		break;

	case COMPONENT_STATE_FOCUSED:
		focused = std::unique_ptr<StyleSet>(style_set);
		break;

	case COMPONENT_STATE_HOVERED:
		hovered = std::unique_ptr<StyleSet>(style_set);
		break;
	}
}
