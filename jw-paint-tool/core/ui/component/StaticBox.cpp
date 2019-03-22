#include "StaticBox.h"

paint_tool::StaticBox::StaticBox(
	const	std::string	&id,
	const	SIZE		&size,
	const	std::string &style_set_id
) :
	Component(id, size, style_set_id) {
	
	willUseBackColour();
	willUsePen();
}

paint_tool::StaticBox::~StaticBox() {
	//
}

void paint_tool::StaticBox::drawComponent(EasyGraphics *ctx) const {

	POINT pos = getAbsolutePosition();
	SIZE size = getSize();
	
	ctx->drawRectangle(pos.x, pos.y, size.cx, size.cy, true);
}