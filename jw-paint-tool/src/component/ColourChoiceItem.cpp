#include "ColourChoiceItem.h"

paint_tool::ColourChoiceItem::ColourChoiceItem(
	const	std::string	&id,
	const	SIZE		&size,
	const	int			&value
) : ChoiceComponent<int>(id, value) {

	setFillBackground(true);
	setMinimumSize(size);
	setBgColour(value);

	//p_component_t box = std::make_unique<StaticBox>(
	//	id + "_box", size
	//);
	//box->setBgColour(value);

	//addComponent(box);
}

paint_tool::ColourChoiceItem::~ColourChoiceItem() {
	//
}
