#include "PaintTool.h"

paint_tool::PaintTool::PaintTool(HINSTANCE hInstance) :
	Window(hInstance, 1280, 800) {

	getRootComponent()->setLayoutStrategy(LAYOUT_HORIZONTAL);

	createStyles();
	createFonts();
	createUI();
	
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
		0x101010,
		0x101010,
		1
	);

	/* orange text colour */

	manager->addStyleSet(
		"ui_panel_header",
		0x3b93ff,
		0x101010,
		0x101010,
		1
	);

	/* blue text colour */

	manager->addStyleSet(
		"ui_panel_sub_header",
		0xfed25b,
		0x101010,
		0x101010,
		1
	);

	/* white text colour */

	manager->addStyleSet(
		"ui_panel_text",
		0xffffff,
		0x101010,
		0x101010,
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
		FW_THIN,
		false,
		false,
		false,
		"Segoe UI"
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
	p_panel->setMinimumSize(SIZE{ 260, 800 });
	p_panel->setLayoutStrategy(LAYOUT_VERTICAL);


	/* the x coordinate of each group within the panel */

	const int left_margin = 15;


	/* 2. create the drawing tools heading label with spacing above and below */

	p_component_t label_drawing_tools = std::make_unique<StaticLabel>(
		"left_panel_label_drawing_tools",
		L"Drawing Tools",
		"ui_panel_header",
		"ui_panel_header"
	);
	label_drawing_tools->setPosition(POINT{ left_margin, 0 });


	/* 2.1 create the tool choice option group */

	p_component_t drawing_tools_choice = std::make_unique<RadioGroup<int>>(
		"drawing_tools_choice",
		SIZE{ 25,25 }
	);
	drawing_tools_choice->setPosition(POINT{ left_margin, 0 });

	RadioGroup<int> *p_drawing_tools_choice = dynamic_cast<RadioGroup<int> *>(drawing_tools_choice.get());

	
	/* 2.1.1 create and add the pens sub heading to the option group */

	p_component_t label_drawing_tools_pens = std::make_unique<StaticLabel>(
		"label_drawing_tools_pens",
		L"Pens",
		"ui_panel_sub_header",
		"ui_panel_sub_header"
	);

	p_drawing_tools_choice->addComponent(label_drawing_tools_pens);


	/* 3. add the created components to the panel */

	p_panel->addVerticalSpace(15);
	p_panel->addComponent(label_drawing_tools);
	p_panel->addVerticalSpace(10);
	p_panel->addComponent(drawing_tools_choice);


	/* final: add the group to the ui */

	addComponent(panel);
}