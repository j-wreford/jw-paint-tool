#include "AppData.h"


const COLORREF paint_tool::AppData::UI_PANEL_BG = 0x101010;
const COLORREF paint_tool::AppData::UI_PANEL_TEXT = 0xffffff;
const COLORREF paint_tool::AppData::UI_PANEL_HEADING = RGB(0xff, 0x93, 0x3b);
const COLORREF paint_tool::AppData::UI_PANEL_SUB_HEADING = RGB(0x5b, 0xd2, 0xfe);
const COLORREF paint_tool::AppData::UI_PANEL_ACTIVE = 0x3f3f3f;
const COLORREF paint_tool::AppData::UI_PANEL_FOCUS = 0x101010;
const COLORREF paint_tool::AppData::UI_PANEL_HOVER = 0x2b2b2b;

paint_tool::AppData::AppData() :
	tool_choice(TOOL_PEN_FREEHAND),
	drawing_choice(nullptr) {
	//
}

paint_tool::AppData::~AppData() {
	//
}