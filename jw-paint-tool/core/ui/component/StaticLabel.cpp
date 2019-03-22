#include "StaticLabel.h"

paint_tool::StaticLabel::StaticLabel(
	const	std::string		&id,
	const	std::wstring	&text,
	const	std::string		&style_set_id ,
	const	std::string		&font_attr_set_id
) :
	Component(id, style_set_id),
	font_attr_set_id(font_attr_set_id),
	text(text) {

	/* we can't pass calculateTextSize() into the Component constructor
	   directly since the text and font properties have not been initialised
	   yet - so set the size here instead */

	setSize(calculateTextSize());
}

paint_tool::StaticLabel::~StaticLabel() {
	//
}

void paint_tool::StaticLabel::drawComponent(EasyGraphics *ctx) const {

	POINT pos = getAbsolutePosition();

	ctx->drawText(text.c_str(), pos.x, pos.y);
}

void paint_tool::StaticLabel::recalculateSize() {
	setSize(calculateTextSize());
}

SIZE paint_tool::StaticLabel::calculateTextSize() const {

	/* get the device context for the entire screen */

	HDC h_dc = GetDC(NULL);

	/* make sure we're using the same font this label is using */

	HFONT h_font = FontManager::getInstance()->getFontHandle(font_attr_set_id);
	::SelectObject(h_dc, h_font);

	/* "draw" the text but offer the DT_CALCRECT format option,
	   so that the text isn't drawn anywhere. Instead the calculated rect around
	   the text is placed into r */

	RECT r = { 0, 0, 0, 0 };
	::DrawText(h_dc, text.c_str(), text.size(), &r, DT_CALCRECT);

	/* release the device context we got */

	::ReleaseDC(NULL, h_dc);
	::DeleteObject(h_font);

	return SIZE{
		r.right - r.left,
		r.bottom - r.top
	};
}