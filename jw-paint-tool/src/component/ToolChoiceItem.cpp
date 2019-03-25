#include "ToolChoiceItem.h"

paint_tool::ToolChoiceItem::ToolChoiceItem(
	const	std::string		&id,
			ToolChoice		value,
	const	std::wstring	&text,
	const	std::wstring	&icon,
	const	std::string		&font_attr_set_id
) : ChoiceComponent<ToolChoice>(id, value) {

	setLayoutStrategy(LAYOUT_HORIZONTAL);
	setFillBackground(true);

	addHorizontalSpace(10);

	if (StaticImage::imageExists(icon)) {

		p_component_t image = std::make_unique<StaticImage>(
			id + "_img",
			StaticImage::getImageSize(icon),
			icon,
			0x101010
		);
		image->setAlignment(ALIGN_MIDDLE);
		addComponent(image);
		addHorizontalSpace(10);
	}

	/* build the label */

	p_component_t label = std::make_unique<StaticLabel>(
		id + "_label",
		text,
		font_attr_set_id
		);
	label->setAlignment(ALIGN_MIDDLE);
	addComponent(label);
	addHorizontalSpace(10);
}

paint_tool::ToolChoiceItem::~ToolChoiceItem() {
	//
}
