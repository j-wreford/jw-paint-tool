#include "ComponentStyle.h"

paint_tool::ComponentStyle::ComponentStyle() {
	
	/* initialise the StyleSet for each ComponentState to guarantee that
	   accessing a map item using ComponentState won't fail */

	state_styleset_map.insert(
		std::make_pair(COMPONENT_STATE_NORMAL, std::make_unique<StyleSet>())
	);

	state_styleset_map.insert(
		std::make_pair(COMPONENT_STATE_ACTIVE, std::make_unique<StyleSet>())
	);

	state_styleset_map.insert(
		std::make_pair(COMPONENT_STATE_FOCUSED, std::make_unique<StyleSet>())
	);

	state_styleset_map.insert(
		std::make_pair(COMPONENT_STATE_HOVERED, std::make_unique<StyleSet>())
	);

	state_styleset_map.insert(
		std::make_pair(COMPONENT_STATE_CHOSEN, std::make_unique<StyleSet>())
	);
}

paint_tool::ComponentStyle::~ComponentStyle() {
	//
}

const paint_tool::ComponentStyle::StyleSet *paint_tool::ComponentStyle::getEffectiveStyleSet(std::vector<ComponentState> states) {

	/* make a new styleset & populate the styleset with values frrom the
	   normal state */

	auto styleset = std::make_unique<StyleSet>();

	StyleSet *normal_styleset = state_styleset_map[COMPONENT_STATE_NORMAL].get();

	if (normal_styleset->text_colour)
		styleset->text_colour = std::make_unique<int>(*normal_styleset->text_colour);

	if (normal_styleset->bg_colour)
		styleset->bg_colour = std::make_unique<int>(*normal_styleset->bg_colour);

	if (normal_styleset->line_colour)
		styleset->line_colour = std::make_unique<int>(*normal_styleset->line_colour);

	if (normal_styleset->line_thickness)
		styleset->line_thickness = std::make_unique<int>(*normal_styleset->line_thickness);

	/* now merge the styles of the given states into the newly made styleset */

	std::for_each(states.begin(), states.end(), [this, &styleset, &states](ComponentState state) {

		StyleSet *state_styleset = state_styleset_map[state].get();

		if (state_styleset->text_colour)
			styleset->text_colour = std::make_unique<int>(*state_styleset->text_colour);

		if (state_styleset->bg_colour)
			styleset->bg_colour = std::make_unique<int>(*state_styleset->bg_colour);

		if (state_styleset->line_colour)
			styleset->line_colour = std::make_unique<int>(*state_styleset->line_colour);

		if (state_styleset->line_thickness)
			styleset->line_thickness = std::make_unique<int>(*state_styleset->line_thickness);
	});

	/* update the effective styleset property and return the pointer to it */

	effective_styleset = std::move(styleset);

	return effective_styleset.get();
}