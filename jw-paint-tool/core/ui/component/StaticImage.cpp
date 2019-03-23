#include "StaticImage.h"

paint_tool::StaticImage::StaticImage(
	const std::string	&id,
	const SIZE			&size,
	const std::wstring	&file_path,
	const int			&transparent = 0xffffff
) : Component(id, size), 
	file_path(file_path),
	transparent(transparent) {
	//
}

paint_tool::StaticImage::~StaticImage() {
	//
}

void paint_tool::StaticImage::drawComponent(EasyGraphics *ctx) const {

	POINT pos = getAbsolutePosition();
	SIZE size = getSize();

	ctx->drawBitmap(file_path.c_str(), pos.x, pos.y, size.cx, size.cy, transparent);
}