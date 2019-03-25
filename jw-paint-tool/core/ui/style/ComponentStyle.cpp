#include "ComponentStyle.h"

paint_tool::ComponentStyle::ComponentStyle() :
	normal(std::make_unique<StyleSet>()),
	active(std::make_unique<StyleSet>()), 
	focused(std::make_unique<StyleSet>()), 
	hovered(std::make_unique<StyleSet>()) {
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

	/* instead of re-writing the above code:
	   
	   1. call the const version of this method by casting this to a (const ComponentStyle *>

	   2. return the result as a const by const casting the returned StyleSet

	*/

	return const_cast<ComponentStyle::StyleSet *>(const_cast<const ComponentStyle *>(this)->getStyleSet(state));
}

void paint_tool::ComponentStyle::setTextColour(const int &colour, ComponentState state) {

	getStyleSet(state)->text_colour = std::make_unique<int>(colour);

	/* if we're setting the colour for normal state, then also set it for the
	   special states if they're not set */

	if (state == COMPONENT_STATE_NORMAL) {

		if (!active->text_colour)
			active->text_colour = std::make_unique<int>(colour);

		if (!focused->text_colour)
			focused->text_colour = std::make_unique<int>(colour);

		if (!hovered->text_colour)
			hovered->text_colour = std::make_unique<int>(colour);
	}
}

void paint_tool::ComponentStyle::setBgColour(const int &colour, ComponentState state) {

	getStyleSet(state)->bg_colour = std::make_unique<int>(colour);

	/* if we're setting the colour for normal state, then also set it for the
	   special states if they're not set */

	if (state == COMPONENT_STATE_NORMAL) {

		if (!active->bg_colour)
			active->bg_colour = std::make_unique<int>(colour);

		if (!focused->bg_colour)
			focused->bg_colour = std::make_unique<int>(colour);

		if (!hovered->bg_colour)
			hovered->bg_colour = std::make_unique<int>(colour);
	}
}

void paint_tool::ComponentStyle::setLineColour(const int &colour, ComponentState state) {

	getStyleSet(state)->line_colour = std::make_unique<int>(colour);

	if (state == COMPONENT_STATE_NORMAL) {

		if (!active->line_colour)
			active->line_colour = std::make_unique<int>(colour);

		if (!focused->line_colour)
			focused->line_colour = std::make_unique<int>(colour);

		if (!hovered->line_colour)
			hovered->line_colour = std::make_unique<int>(colour);
	}
}

void paint_tool::ComponentStyle::setLineThickness(const int &thickness, ComponentState state) {

	getStyleSet(state)->line_thickness = std::make_unique<int>(thickness);

	if (state == COMPONENT_STATE_NORMAL) {

		if (!active->line_thickness)
			active->line_thickness = std::make_unique<int>(thickness);

		if (!focused->line_thickness)
			focused->line_thickness = std::make_unique<int>(thickness);

		if (!hovered->line_thickness)
			hovered->line_thickness = std::make_unique<int>(thickness);
	}
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

