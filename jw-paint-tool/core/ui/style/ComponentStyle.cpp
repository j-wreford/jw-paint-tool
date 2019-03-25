#include "ComponentStyle.h"

paint_tool::ComponentStyle::ComponentStyle() {
	//
}

paint_tool::ComponentStyle::~ComponentStyle() {
	//
}

const paint_tool::ComponentStyle::StyleSet *paint_tool::ComponentStyle::getStyleSet(ComponentState state) const {

	StyleSet *style_set = nullptr;

	auto it = std::find(state_styleset_map.begin(), state_styleset_map.end(), state);

	if (it != state_styleset_map.end())
		style_set = it->second.get();
	
	return style_set;
}

paint_tool::ComponentStyle::StyleSet *paint_tool::ComponentStyle::getStyleSet(ComponentState state) {
	return const_cast<ComponentStyle::StyleSet *>(const_cast<const ComponentStyle *>(this)->getStyleSet(state));
}

void paint_tool::ComponentStyle::setTextColour(const int &colour, ComponentState state) {

	StyleSet *style_set = getStyleSet(state);
	if (style_set)
		style_set->text_colour = std::make_unique<int>(colour);

	/* if we're setting the colour for normal state, then also set it for the
	   special states if they're not set. this fixes unexpected colours being
	   used when the Component the StyleSet is for is given a different state */

	if (state == COMPONENT_STATE_NORMAL) {

		for (auto &pair : state_styleset_map) {

			if (!pair.second->text_colour)
				pair.second->text_colour = std::make_unique<int>(colour);
		}
	}
}

void paint_tool::ComponentStyle::setBgColour(const int &colour, ComponentState state) {

	StyleSet *style_set = getStyleSet(state);
	if (style_set)
		style_set->bg_colour = std::make_unique<int>(colour);

	/* if we're setting the colour for normal state, then also set it for the
	   special states if they're not set. this fixes unexpected colours being
	   used when the Component the StyleSet is for is given a different state */

	if (state == COMPONENT_STATE_NORMAL) {

		for (auto &pair : state_styleset_map) {

			if (!pair.second->bg_colour)
				pair.second->bg_colour = std::make_unique<int>(colour);
		}
	}
}

void paint_tool::ComponentStyle::setLineColour(const int &colour, ComponentState state) {

	StyleSet *style_set = getStyleSet(state);
	if (style_set)
		style_set->line_colour = std::make_unique<int>(colour);

	/* if we're setting the colour for normal state, then also set it for the
	   special states if they're not set. this fixes unexpected colours being
	   used when the Component the StyleSet is for is given a different state */

	if (state == COMPONENT_STATE_NORMAL) {

		for (auto &pair : state_styleset_map) {

			if (!pair.second->line_colour)
				pair.second->line_colour = std::make_unique<int>(colour);
		}
	}
}

void paint_tool::ComponentStyle::setLineThickness(const int &thickness, ComponentState state) {

	StyleSet *style_set = getStyleSet(state);
	if (style_set)
		style_set->line_thickness = std::make_unique<int>(thickness);

	/* if we're setting the colour for normal state, then also set it for the
	   special states if they're not set. this fixes unexpected colours being
	   used when the Component the StyleSet is for is given a different state */

	if (state == COMPONENT_STATE_NORMAL) {

		for (auto &pair : state_styleset_map) {

			if (!pair.second->line_thickness)
				pair.second->line_thickness = std::make_unique<int>(thickness);
		}
	}
}