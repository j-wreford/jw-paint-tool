#include "Window.h"

paint_tool::Window::Window(
			HINSTANCE	hInstance,
	const	int			&width,
	const	int			&height
) :
	lmouse_down(false),
	debug_show_ids(false),
	debug_show_borders(false),
	debug_show_position_lines(false) {

	create(hInstance, width, height, 80, false);
	setImmediateDrawMode(false);
	//ClipCursor();

	::SetWindowText(getHWND(), L"Paint Tool! OOP4CS Assignment 2");

	StyleManager::getInstance()->addStyleSet(
		"window_style",
		0x000000,
		0x090909,
		0x090909,
		1
	);

	root_component = std::make_unique<RootComponent>(
		"window_style",
		getHWND()
	);
}

paint_tool::Window::~Window() {
	
	FontManager::destroyInstance();
	StyleManager::destroyInstance();
}

void paint_tool::Window::onDraw() {

	clrscr(0x000000);
	
	Window::componentWalker(
		root_component.get(),
		std::bind(&Window::drawSingleComponent, this, std::placeholders::_1)
	);

	EasyGraphics::onDraw();
}

void paint_tool::Window::onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	//if (nChar == (UINT) 'B')
	//	debugSetShowBorders(!debug_show_borders);

	//onDraw();
}

void paint_tool::Window::onChar(UINT nChar, UINT nRepCnt, UINT nFlags) {

	if (nChar == (UINT) 'i')
		debug_show_ids ^= true;

	if (nChar == (UINT) 'b')
		debug_show_borders ^= true;

	if (nChar == (UINT) 'l')
		debug_show_position_lines ^= true;
	
	if (nChar == (UINT) 'a') {
		debug_show_ids = true;
		debug_show_borders = true;
		debug_show_position_lines = true;
	}

	if (nChar == (UINT) '`') {
		debug_show_ids = false;
		debug_show_borders = false;
		debug_show_position_lines = false;
	}

	onDraw();
}

void paint_tool::Window::onLButtonDown(UINT nFlags, int x, int y) {

	if (root_component->isInteractive())
		root_component->hitTest(POINT{ x, y });

	lmouse_down = true;

	onDraw();
}

void paint_tool::Window::onLButtonUp(UINT nFlags, int x, int y) {
	lmouse_down = false;

	onDraw();
}

void paint_tool::Window::onMouseMove(UINT nFlags, int x, int y) {
	
	if (lmouse_down)
		root_component->onMouseMove(POINT{ x,y });

	onDraw();
}

void paint_tool::Window::addComponent(paint_tool::p_component_t &component) {
	root_component->addComponent(component);
}

void paint_tool::Window::drawSingleComponent(const Component *component) {

	/* adjust the style set being used */

	StyleManager::getInstance()->applyStyleSet(
		component->getStyleSetId(),
		this
	);

	/* adjust the font being used if this component is a label */

	if (component->getComponentType() == paint_tool::CPMNT_STATIC_LABEL) {

		const StaticLabel *label =
			dynamic_cast<const StaticLabel *>(component);

		if (label)
			setHDEFFont(
				FontManager::getInstance()->getFontHandle(
					label->getFontAttributeSetId()
				)
			);
	}

	component->drawComponent(this);

	/* draw debug graphics if the corresponding flag is set */

	if (debug_show_ids)
		drawDebugComponentId(component);

	if (debug_show_borders)
		drawDebugComponentBorder(component);

	if (debug_show_position_lines)
		drawDebugComponentPositionLines(component);
}

void paint_tool::Window::drawDebugComponentId(const Component *component) {

	POINT pos = component->getAbsolutePosition();
	int dy = (component->isComponentGroup() ? -25 : -13);

	/* convert the id string into a wchar string */

	std::string id = component->getId();
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, id.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, id.c_str(), -1, wstr, wchars_num);

	/* get a font handle for the debug id font and draw the text */

	HFONT debug_id_font = FontManager::getInstance()->getFontHandle("debug_id");
	setHDEFFont(debug_id_font);
	selectTextColour(0xff00ff);
	drawText(wstr, pos.x, pos.y + dy);

	/* memory cleanup  */

	::DeleteObject(debug_id_font);
	delete[] wstr;
}

void paint_tool::Window::drawDebugComponentBorder(const Component *component) {

	POINT pos = component->getAbsolutePosition();
	SIZE size = component->getSize();

	/* differentiate between group borders and normal component borders */

	if (component->isComponentGroup())
		setPenColour(0xffff00, 1);
	else
		setPenColour(0x00ffff, 1);

	drawRectangle(pos.x - 1, pos.y - 1, size.cx + 2, size.cy + 2, false);
}

void paint_tool::Window::drawDebugComponentPositionLines(const Component *component) {

	RECT rect = component->getAbsoluteRect();
	SIZE size = component->getSize();

	int half_w = size.cx / 2;
	int half_h = size.cy / 2;

	RECT parent_rect;

	/* if this component doesn't have a parent, then use the rectangle of the
	   EasyGraphics window */

	if (component->getParent())
		parent_rect = component->getParent()->getAbsoluteRect();
	else
		::GetClientRect(getHWND(), &parent_rect);

	/* differentiate between group position lines and normal component position lines */

	if (component->isComponentGroup())
		setPenColour(0xffff00, 1);
	else
		setPenColour(0x00ffff, 1);

	/* top, bottom, left, right */
	
	drawLine(rect.left + half_w, rect.top - 1, rect.left + half_w, parent_rect.top);
	drawLine(rect.left + half_w, rect.bottom + 1, rect.left + half_w, parent_rect.bottom);
	drawLine(rect.left - 1, rect.top + half_h, parent_rect.left, rect.top + half_h);
	drawLine(rect.right + 1, rect.top + half_h, parent_rect.right, rect.top + half_h);
}

void paint_tool::Window::componentWalker(
	Component *component,
	std::function<void(Component *component)> fn
) {

	/* execute the function given with the currently visited component
	   as its argument */

	fn(component);

	/* decend into this components children if it's a ComponentGroup */

	if (component->isComponentGroup()) {

		const ComponentGroup *group =
			dynamic_cast<const ComponentGroup *>(component);

		for (auto &pair : *group->getChildComponents())
			Window::componentWalker(pair.second.get(), fn);
	}

}