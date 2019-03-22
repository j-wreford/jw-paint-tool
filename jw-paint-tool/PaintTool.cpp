#include "PaintTool.h"

paint_tool::PaintTool::PaintTool(HINSTANCE hInstance) :
	Window(hInstance, 1280, 800) {

	createStyles();
	createFonts();
	createUI();

	getRootComponent()->setLayoutStrategy(LAYOUT_HORIZONTAL);
	
	waitForClose();
}

paint_tool::PaintTool::~PaintTool() {
	//
}

void paint_tool::PaintTool::createStyles() {

	StyleManager *manager = StyleManager::getInstance();
	
	/* dark-grey background with white text */

	manager->addStyleSet(
		"ui_panel",
		0xffffff,
		0x2a2a2a,
		0x2a2a2a,
		1
	);

	/* orange text colour */

	manager->addStyleSet(
		"ui_panel_header",
		0x3b93ff,
		0x2a2a2a,
		0x2a2a2a,
		1
	);

	/* blue text colour */

	manager->addStyleSet(
		"ui_panel_sub_header",
		0xfed25b,
		0x2a2a2a,
		0x2a2a2a,
		1
	);

	/* white text colour */

	manager->addStyleSet(
		"ui_panel_text",
		0xffffff,
		0x2a2a2a,
		0x2a2a2a,
		1
	);

	/* canvas white background */

	manager->addStyleSet(
		"canvas_background",
		0xffffff,
		0xffffff,
		0xffffff,
		1
	);
}

void paint_tool::PaintTool::createFonts() {

	FontManager *manager = FontManager::getInstance();

	/* heading font */

	manager->addFontAttributeSet(
		"ui_panel_header",
		27,
		FW_DONTCARE,
		false,
		false,
		false,
		"Segoe UI Semibold"
	);

	/* subheading font */

	manager->addFontAttributeSet(
		"ui_panel_sub_header",
		23,
		FW_THIN,
		false,
		false,
		false,
		"Segoe UI"
	);
}

void paint_tool::PaintTool::createUI() {

	createLeftPanel();
	createCanvas();
}

void paint_tool::PaintTool::createCanvas() {

	/* temporary: create a white box to simulate the canvas */

	p_component_t canvas = std::make_unique<StaticBox>(
		"simulated_canvas",
		SIZE{ 1020, 800 },
		"canvas_background"
	);
	addComponent(canvas);
}

void paint_tool::PaintTool::createLeftPanel() {

	/* 1. create the base group for the panel */

	p_component_t panel = std::make_unique<ComponentGroup>(
		"left_panel",
		"ui_panel",
		true // fill background
	);
	ComponentGroup *p_panel = dynamic_cast<ComponentGroup *>(panel.get());


	/* 2. create a box to force the panel size */

	p_component_t box = std::make_unique<StaticBox>(
		"left_panel_box",
		SIZE{ 260, 800 },
		"ui_panel"
	);
	p_panel->addComponent(box);


	/* 3. create the drawing tools heading label */

	p_component_t label_drawing_tools = std::make_unique<StaticLabel>(
		"left_panel_label_drawing_tools",
		POINT{ 10, 15 },
		L"Drawing Tools",
		"ui_panel_header",
		"ui_panel_header"
	);
	p_panel->addComponent(label_drawing_tools);


	/* final: add the group to the ui */

	addComponent(panel);
}