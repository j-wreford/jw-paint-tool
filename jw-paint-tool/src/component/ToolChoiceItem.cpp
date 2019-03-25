#include "ToolChoiceItem.h"

paint_tool::ToolChoiceItem::ToolChoiceItem(
	const	std::string		&id,
			ToolChoice		value,
	const	std::wstring	&text,
	const	std::string		&font_attr_set_id = "default"
) : RadioItem<ToolChoice>(id, value, text, font_attr_set_id) {
	
	/* we want to show the background for this item */

	setFillBackground(true);
}

paint_tool::ToolChoiceItem::~ToolChoiceItem() {
	//
}
