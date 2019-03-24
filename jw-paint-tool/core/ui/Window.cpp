#include "Window.h"

paint_tool::Window::Window(
			HINSTANCE	hInstance,
	const	int			&width,
	const	int			&height
) :
	lmouse_down(false),
	debug_show_ids(false),
	debug_show_pos(false),
	debug_show_borders(false),
	debug_show_position_lines(false) {

	create(hInstance, width, height, 80, false);
	setImmediateDrawMode(false);

	/*
	RECT rect;
	::GetWindowRect(getHWND(), &rect);
	::ClipCursor(&rect);
	*/

	::SetWindowText(getHWND(), L"User Interface Window");

	root_component = std::make_unique<ComponentGroup>(
		"root",
		"window_style",
		true
	);
	root_component->setMinimumSize(SIZE{ width, height });

	StyleManager::getInstance()->addStyleSet(
		"window_style",
		0x000000,
		0x090909,
		0x090909,
		1
	);
}

paint_tool::Window::~Window() {
	
	FontManager::destroyInstance();
	StyleManager::destroyInstance();
}

void paint_tool::Window::onDraw() {

	if (!root_component)
		return;

	clrscr(0x000000);

	LayoutManager *layout_manager = new LayoutManager();
	layout_manager->layout(root_component.get());

	componentDrawer(root_component.get(), 0x000000, 0xffffff, 0xffffff, 1);

	EasyGraphics::onDraw();

	delete layout_manager;
}

void paint_tool::Window::onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	//if (nChar == (UINT) 'B')
	//	debugSetShowBorders(!debug_show_borders);

	//onDraw();
}

void paint_tool::Window::onChar(UINT nChar, UINT nRepCnt, UINT nFlags) {

	if (nChar == (UINT) 'i')
		debug_show_ids ^= true;

	if (nChar == (UINT) 'p')
		debug_show_pos ^= true;

	if (nChar == (UINT) 'b')
		debug_show_borders ^= true;

	if (nChar == (UINT) 'l')
		debug_show_position_lines ^= true;
	
	if (nChar == (UINT) 'a') {
		debug_show_ids = true;
		debug_show_pos = true;
		debug_show_borders = true;
		debug_show_position_lines = true;
	}

	if (nChar == (UINT) '`') {
		debug_show_ids = false;
		debug_show_pos = false;
		debug_show_borders = false;
		debug_show_position_lines = false;
	}

	onDraw();
}

void paint_tool::Window::onLButtonDown(UINT nFlags, int x, int y) {

	if (!root_component)
		return;

	/* the root component should always have been hit, but perform a
	   test anyway to be safe */

	if (root_component->wasHit(POINT{ x, y }))
		root_component->onLeftMouseDownHit(POINT{ x, y });

	lmouse_down = true;

	onDraw();
}

void paint_tool::Window::onLButtonUp(UINT nFlags, int x, int y) {

	if (!root_component)
		return;

	/* the root component should always have been hit, but perform a
       test anyway to be safe */

	if (root_component->wasHit(POINT{ x, y }))
		root_component->onLeftMouseUpHit(POINT{ x, y });

	lmouse_down = false;

	onDraw();
}

void paint_tool::Window::onMouseMove(UINT nFlags, int x, int y) {

	if (!root_component)
		return;
	
	/* the root component should always have been hit, but perform a
       test anyway to be safe */

	if (root_component->wasHit(POINT{ x,y }))
		root_component->onMouseMoveHit(POINT{ x, y }, lmouse_down);

	onDraw();
}

paint_tool::ComponentGroup *paint_tool::Window::getRootComponent() {
	return root_component.get();
}

void paint_tool::Window::addComponent(paint_tool::p_component_t &component) {
	root_component->addComponent(component);
}

void paint_tool::Window::drawSingleComponent(const Component *component) {

	/* adjust the colours being used */

	const ComponentStyle::StyleSet *style_set = component->getStyleSet();

	if (style_set->text_colour)
		selectTextColour(*style_set->text_colour);

	if (style_set->bg_colour)
		selectBackColour(*style_set->bg_colour);

	if (style_set->line_colour && style_set->line_thickness)
		setPenColour(*style_set->line_colour, *style_set->line_thickness);
	else {

		HDC hdc = GetDC(getHWND());

		if (style_set->line_colour)
			::SetDCPenColor(hdc, *style_set->line_colour);
		else if (style_set->line_thickness) {

			COLORREF current_line_colour = ::GetDCPenColor(hdc);

			setPenColour(current_line_colour, *style_set->line_thickness);
		}

		::ReleaseDC(getHWND(), hdc);
	}


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

	if (debug_show_pos)
		drawDebugComponentPos(component);

	if (debug_show_borders)
		drawDebugComponentBorder(component);

	if (debug_show_position_lines)
		drawDebugComponentPositionLines(component);
}

void paint_tool::Window::componentDrawer(
	const Component *component,
	int	current_text_col,
	int	current_bg_col,
	int	current_line_col,
	int	current_line_thickness
) {

	/* 1. adjust the colours being used and update the current_ variables
		  so these can be set again after a child component changes them */

	const ComponentStyle::StyleSet *style_set = component->getStyleSet();

	/* adjust text colour */

	if (style_set->text_colour) {
		selectTextColour(*style_set->text_colour);
		current_text_col = *style_set->text_colour;
	}

	/* adjust background colour */

	if (style_set->bg_colour) {
		selectBackColour(*style_set->bg_colour);
		current_bg_col = *style_set->bg_colour;
	}

	/* adjust pen colour & thickness */

	if (style_set->line_colour && style_set->line_thickness) {
		setPenColour(*style_set->line_colour, *style_set->line_thickness);
		current_line_col = *style_set->line_colour;
		current_line_thickness = *style_set->line_thickness;
	}
	else if (style_set->line_colour) {
		setPenColour(*style_set->line_colour, current_line_thickness);
		current_line_col = *style_set->line_colour;
	}
	else if (style_set->line_thickness) {
		setPenColour(current_line_col, *style_set->line_thickness);
		current_line_thickness = *style_set->line_thickness;
	}

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

	/* draw the component */

	component->drawComponent(this);

	/* draw debug graphics if the corresponding flag is set */

	if (debug_show_ids)
		drawDebugComponentId(component);

	if (debug_show_pos)
		drawDebugComponentPos(component);

	if (debug_show_borders)
		drawDebugComponentBorder(component);

	if (debug_show_position_lines)
		drawDebugComponentPositionLines(component);

	/* draw child components, if any */

	if (component->isComponentGroup()) {

		const ComponentGroup *group =
			dynamic_cast<const ComponentGroup *>(component);

		for (const p_component_t &child : *group->getChildComponents()) {

			/* draw the child component */

			componentDrawer(child.get(), current_text_col, current_bg_col, current_line_col, current_line_thickness);

			/* reset the colours for the next child component to use */

			selectTextColour(current_text_col);
			selectBackColour(current_bg_col);
			setPenColour(current_line_col, current_line_thickness);
		}
	}
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

	//::DeleteObject(debug_id_font); Doesn't need to be deleted? setHDEFFont does this
	delete[] wstr;
}

void paint_tool::Window::drawDebugComponentPos(const Component *component) {

	SIZE size = component->getSize();
	POINT pos = component->getPosition();
	POINT abs_pos = component->getAbsolutePosition();

	int dy = (component->isComponentGroup() ? 25 : 5);

	std::wstring wstr = L"(x=" + std::to_wstring(pos.x) + L", y=" + std::to_wstring(pos.y) + L") " + 
		L" [" + std::to_wstring(size.cx) + L"x" + std::to_wstring(size.cy) + L"]";

	HFONT debug_id_font = FontManager::getInstance()->getFontHandle("debug_id");
	setHDEFFont(debug_id_font);
	selectTextColour(0xff00ff);
	drawText(wstr.c_str(), abs_pos.x, abs_pos.y + component->getSize().cy + dy);

	::DeleteObject(debug_id_font);
}

void paint_tool::Window::drawDebugComponentBorder(const Component *component) {

	POINT pos = component->getAbsolutePosition();
	SIZE size = component->getSize();
	POINT origin = component->getOrigin();

	/* draw the origin */

	int x1, y1, x2, y2;
	x1 = pos.x + origin.x - 5;
	y1 = pos.y + origin.y - 5;
	x2 = pos.x + origin.x + 5;
	y2 = pos.y + origin.y + 5;

	setPenColour(0x0000ff, 1);
	drawLine(x1, y1, x2, y2);
	drawLine(x1, y2, x2, y1);
	drawCircle(pos.x + origin.x, pos.y + origin.y, 5, false);
	//drawLine(pos.x + origin.x - 5, pos.y + origin.y - 5, pos.x + origin.x + 5, pos.y + origin.y + 5);

	/* differentiate between group borders and normal component borders */

	if (component->isComponentGroup())
		setPenColour(0xffff00, 1);
	else
		setPenColour(0x00ffff, 1);

	drawRectangle(pos.x - 1, pos.y - 1, size.cx + 2, size.cy + 2, false);

	/* if this component is active, focused, or hovered, indicate it with further
	   borders */

	if (component->isInteractive()) {

		const InteractiveComponent *temp =
			dynamic_cast<const InteractiveComponent *>(component);

		if (temp->isActive()) {
			setPenColour(0x0000ff, 1);
			drawRectangle(pos.x - 5, pos.y - 5, size.cx + 10, size.cy + 10, false);
		}

		if (temp->isFocused()) {
			setPenColour(0xf0f0f0, 1);
			drawRectangle(pos.x - 3, pos.y - 3, size.cx + 6, size.cy + 6, false);
		}

		if (temp->isHovered()) {
			setPenColour(0x00ff00, 1);
			drawRectangle(pos.x - 7, pos.y - 7, size.cx + 14, size.cy + 14, false);
		}
	}
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

	/* differentiate between group position lines and normal component position
	   lines */

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

		for (const p_component_t &child : *group->getChildComponents())
			Window::componentWalker(child.get(), fn);
	}
}