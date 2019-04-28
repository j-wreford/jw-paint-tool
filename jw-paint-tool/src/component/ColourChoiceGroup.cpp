#include "ColourChoiceGroup.h"

paint_tool::ColourChoiceGroup::ColourChoiceGroup(const std::string &id, const int &default_col) :
	ChoiceGroup<int>(id, default_col) {
	
	setLayoutStrategy(LAYOUT_HORIZONTAL);

	p_component_t col_choice_red = makeColourChoiceItem("fill_col_red", RGB(0xff, 0x0, 0x0));
	addComponent(col_choice_red);
	addHorizontalSpace(15);

	p_component_t col_choice_green = makeColourChoiceItem("fill_col_green", RGB(0x00, 0xff, 0x00));
	addComponent(col_choice_green);
	addHorizontalSpace(15);

	p_component_t col_choice_blue = makeColourChoiceItem("fill_col_blue", RGB(0x00, 0x0, 0xff));
	addComponent(col_choice_blue);
	addHorizontalSpace(15);
}

paint_tool::ColourChoiceGroup::~ColourChoiceGroup() {
	//
}

paint_tool::p_component_t paint_tool::ColourChoiceGroup::makeColourChoiceItem(
	const	std::string	&id,
	const	int			&value
) {

	p_component_t colour_choice = std::make_unique<ColourChoiceItem>(
		id, SIZE{ 25, 25 }, value
	);

	colour_choice->setLineThickness(2);
	colour_choice->setLineColour(0xffffff, COMPONENT_STATE_CHOSEN);

	return colour_choice;
}