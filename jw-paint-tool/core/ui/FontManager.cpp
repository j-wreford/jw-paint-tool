#include "FontManager.h"

paint_tool::FontManager::FontManager() {
	addFontAttributeSet("default", 20, FW_DONTCARE, false, false, false, "Calibri");
	addFontAttributeSet("debug_id", 12, FW_DONTCARE, false, false, false, "Calibri");
}

paint_tool::FontManager::~FontManager() {

	for (auto& pair : font_attr_map)
		delete pair.second;
}

void paint_tool::FontManager::addFontAttributeSet(
	const	std::string &font_attr_set_id,
	const	int			&height,
	const	int			&weight,
	const	bool		&italic,
	const	bool		&underline,
	const	bool		&strikeout,
	const	std::string &font_face
) {

	/* bail if there's already a pair within the map with the same key */

	if (font_attr_map.find(font_attr_set_id) != font_attr_map.end())
		return;

	LOGFONT *logfont = new LOGFONT;
	logfont->lfHeight = height;
	logfont->lfWidth = 0;
	logfont->lfEscapement = 0;
	logfont->lfOrientation = 0;
	logfont->lfWeight = weight;
	logfont->lfItalic = italic;
	logfont->lfUnderline = underline;
	logfont->lfStrikeOut = strikeout;
	logfont->lfCharSet = DEFAULT_CHARSET;
	logfont->lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont->lfQuality = DEFAULT_QUALITY;
	logfont->lfPitchAndFamily = DEFAULT_PITCH;
	MultiByteToWideChar(CP_ACP, 0, font_face.c_str(), -1, logfont->lfFaceName, font_face.length());

	font_attr_map.insert(std::make_pair(
		font_attr_set_id, logfont
	));
}

HFONT paint_tool::FontManager::getFontHandle(const std::string &font_attr_set_id) {

	/* bail if the key doesn't exist */

	auto search = font_attr_map.find(font_attr_set_id);

	if (search == font_attr_map.end())
		search = font_attr_map.find("default");

	return ::CreateFontIndirect(search->second);
}