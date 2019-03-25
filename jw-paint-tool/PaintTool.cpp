#include "PaintTool.h"

paint_tool::PaintTool::PaintTool(HINSTANCE hInstance) :
	Window(hInstance, 1280, 800),
	ui_panel_bg(0x101010),
	ui_panel_text(0xffffff),
	ui_panel_heading(RGB(0xff, 0x93, 0x3b)),
	ui_panel_sub_heading(RGB(0x5b, 0xd2, 0xfe)) {

	::SetWindowText(getHWND(), L"Paint Tool");

	getRootComponent()->setLayoutStrategy(LAYOUT_HORIZONTAL);

	createFonts();
	createUI();
	
	waitForClose();
}

paint_tool::PaintTool::~PaintTool() {
	//
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
		20,
		FW_THIN,
		false,
		false,
		false,
		"Segoe UI"
	);

	/* body font */

	manager->addFontAttributeSet(
		"ui_panel_body",
		18,
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
		SIZE{ 1020, 800 }
	);
	canvas->setBgColour(0xffffff);
	addComponent(canvas);
}

void paint_tool::PaintTool::createLeftPanel() {

	/* 1. create the base group for the panel */

	p_component_t panel = std::make_unique<ComponentGroup>(
		"left_panel",
		true // fill background
	);
	ComponentGroup *p_panel = dynamic_cast<ComponentGroup *>(panel.get());
	p_panel->setMinimumSize(SIZE{ 260, 800 });
	p_panel->setLayoutStrategy(LAYOUT_VERTICAL);

	p_panel->setBgColour(ui_panel_bg);
	p_panel->setTextColour(ui_panel_text);
	p_panel->setLineColour(ui_panel_bg);


	/* the x coordinate of each group within the panel */

	const int left_margin = 30;


	/* 2. create the tools heading label with spacing above and below */

	p_component_t label_tools = std::make_unique<StaticLabel>(
		"left_panel_label_tools",
		L"Tools",
		"ui_panel_header"
	);
	label_tools->setPosition(POINT{ left_margin, 0 });
	label_tools->setTextColour(ui_panel_heading);


	/* 2.1 create the tool choice option group */

	p_component_t tools_choice = std::make_unique<RadioGroup<int>>(
		"tools_choice",
		"ui_panel_body"
	);
	tools_choice->setPosition(POINT{ left_margin, 0 });

	RadioGroup<int> *p_tools_choice = dynamic_cast<RadioGroup<int> *>(tools_choice.get());
	p_tools_choice->setLayoutStrategy(LAYOUT_VERTICAL);


	/* 2.1.0 create and add the management sub heading and options to the
	   choice group */

	p_component_t label_tools_management = std::make_unique<StaticLabel>(
		"label_tools_management",
		L"Management",
		"ui_panel_sub_header"
	);
	label_tools_management->setTextColour(ui_panel_sub_heading);

	p_tools_choice->addComponent(label_tools_management);
	p_tools_choice->addVerticalSpace(10);
	p_tools_choice->addChoice(1, "tool_move", L"Move");
	p_tools_choice->addVerticalSpace(10);
	p_tools_choice->addChoice(2, "tool_del", L"Delete");

	
	/* 2.1.1 create and add the pens sub heading and options to the choice
	   group */

	p_component_t label_tools_pens = std::make_unique<StaticLabel>(
		"label_tools_pens",
		L"Pens",
		"ui_panel_sub_header"
	);
	label_tools_pens->setTextColour(ui_panel_sub_heading);

	p_tools_choice->addVerticalSpace(25);
	p_tools_choice->addComponent(label_tools_pens);
	p_tools_choice->addVerticalSpace(10);
	p_tools_choice->addChoice(3, "tool_pen_freehand", L"Freehand");
	p_tools_choice->addVerticalSpace(10);
	p_tools_choice->addChoice(4, "tool_pen_line", L"Line");


	/* 2.1.2 create and add the shapes sub heading and options */

	p_component_t label_tools_shapes = std::make_unique<StaticLabel>(
		"label_tools_shapes",
		L"Shapes",
		"ui_panel_sub_header"
	);
	label_tools_shapes->setTextColour(ui_panel_sub_heading);

	p_tools_choice->addVerticalSpace(25);
	p_tools_choice->addComponent(label_tools_shapes);
	p_tools_choice->addVerticalSpace(10);
	p_tools_choice->addChoice(5, "tool_shape_tri", L"Triangle");
	p_tools_choice->addVerticalSpace(10);
	p_tools_choice->addChoice(6, "tool_shape_rect", L"Rectangle");
	p_tools_choice->addVerticalSpace(10);
	p_tools_choice->addChoice(7, "tool_shape_circle", L"Circle");
	p_tools_choice->addVerticalSpace(10);
	p_tools_choice->addChoice(8, "tool_shape_star", L"Star");


	/* 3. add the created components to the panel */

	p_panel->addVerticalSpace(25);
	p_panel->addComponent(label_tools);
	p_panel->addVerticalSpace(25);
	p_panel->addComponent(tools_choice);


	/* final: add the group to the ui */

	addComponent(panel);
}