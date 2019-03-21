#include "InternalRadioItem.h"

template <class ValT>
paint_tool::InternalRadioItem<ValT>::InternalRadioItem(
	const	std::string	&id,
	const	POINT		&position,
	const	SIZE		&size,
			ValT		value,
	const	std::string &style_set_id
) :
	InteractiveComponent(id, position, style_set_id),
	value(value) {
	//
}

template <class ValT>
paint_tool::InternalRadioItem<ValT>::~InternalRadioItem() {
	//
}

template <class ValT>
void paint_tool::InternalRadioItem<ValT>::drawComponent(EasyGraphics *ctx) {

	POINT pos = getAbsolutePosition();

	ctx->drawCircle(pos.x, pos.y, getSize().cx, false);

	if (isFocused())
		ctx->drawCircle(pos.x, pos.y, getSize().cx / 2, false);
}

template <class ValT>
ValT paint_tool::InternalRadioItem<ValT>::getValue() const {
	return value;
}