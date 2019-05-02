#include "ColourChoiceItem.h"

paint_tool::ColourChoiceItem::ColourChoiceItem(
	const	std::string	&id,
	const	SIZE		&size,
	const	int			&value
) : ChoiceComponent<int>(id, value) {
	
	setFillBackground(true);

	setBgColour(AppData::UI_PANEL_HOVER);
	setLineColour(AppData::UI_PANEL_ACTIVE);
	setLineThickness(2);

	setBgColour(0x808080, COMPONENT_STATE_HOVERED);
	setLineColour(0xa0a0a0, COMPONENT_STATE_HOVERED);

	setBgColour(0xffffff, COMPONENT_STATE_CHOSEN);
	setLineColour(AppData::UI_PANEL_BG, COMPONENT_STATE_CHOSEN);

	setMinimumSize(size);

	p_component_t colour = std::make_unique<StaticBox>(
		id + "_colour", SIZE{ size.cx - 4, size.cy - 4 }
	);
	colour->setPosition(POINT{ 2, 2 });
	colour->setBgColour(value);
	colour->setLineColour(AppData::UI_PANEL_BG);
	colour->setLineThickness(2);

	addComponent(colour);
}

paint_tool::ColourChoiceItem::~ColourChoiceItem() {
	//
}
