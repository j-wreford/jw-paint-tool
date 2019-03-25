#include "StaticBox.h"

paint_tool::StaticBox::StaticBox(
	const	std::string	&id,
	const	SIZE		&size
) :
	Component(id, size) {
	
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