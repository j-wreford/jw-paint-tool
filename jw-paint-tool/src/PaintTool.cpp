#include "PaintTool.h"


paint_tool::PaintTool::PaintTool(HINSTANCE hInstance) :
	Window(hInstance, 1540, 800) {

	::SetWindowText(getHWND(), L"Paint Tool");

	getRootComponent()->setLayoutStrategy(LAYOUT_HORIZONTAL);

	createFonts();
	createUI();
	
	onDraw();
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
	createRightPanel();
}

void paint_tool::PaintTool::createCanvas() {

	p_component_t canvas = std::make_unique<Canvas>(
		"canvas"
	);
	canvas->setBgColour(0xffffff);

	if (Canvas *p_canvas = dynamic_cast<Canvas *>(canvas.get())) {

		p_canvas->setMinimumSize(SIZE{ 1020, 800 });

		/* inform the file i/o system that this is the Canvas we want to use
		   when saving or loading to or from a file */

		PaintToolFileIO::getInstance()->setCanvasPointer(p_canvas);
	}

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

	p_panel->setBgColour(AppData::UI_PANEL_BG);
	p_panel->setTextColour(AppData::UI_PANEL_TEXT);
	p_panel->setLineColour(AppData::UI_PANEL_BG);


	/* the x coordinate of each group within the panel */

	const int left_margin = 30;


	/* 2. create the tools heading label with spacing above and below */

	p_component_t label_tools = std::make_unique<StaticLabel>(
		"left_panel_label_tools",
		L"Tools",
		"ui_panel_header"
	);
	label_tools->setPosition(POINT{ left_margin, 0 });
	label_tools->setTextColour(AppData::UI_PANEL_HEADING);


	/* 2.1 create the tool choice option group */

	p_component_t tools_choice = std::make_unique<ChoiceGroup<ToolChoice>>(
		"tools_choice", TOOL_MOVE
	);
	tools_choice->setPosition(POINT{ left_margin, 0 });

	ChoiceGroup<ToolChoice> *p_tools_choice = dynamic_cast<ChoiceGroup<ToolChoice> *>(tools_choice.get());
	p_tools_choice->setLayoutStrategy(LAYOUT_VERTICAL);

	/* enable AppData to respond to changes to the value of the tool choice
	   option group */

	p_tools_choice->registerObserver(AppData::getInstance());

	/* 2.1.0 create and add the management sub heading and options to the
	   choice group */

	p_component_t label_tools_management = std::make_unique<StaticLabel>(
		"label_tools_management",
		L"Management",
		"ui_panel_sub_header"
	);
	label_tools_management->setTextColour(AppData::UI_PANEL_SUB_HEADING);
	p_tools_choice->addComponent(label_tools_management);
	p_tools_choice->addVerticalSpace(15);

	p_component_t tool_choice_move = makeToolChoiceItem("tool_move", TOOL_MOVE, L"Move", L"tools_choice_tool_move");
	p_tools_choice->addComponent(tool_choice_move);
	p_tools_choice->addVerticalSpace(15);

	p_component_t tool_choice_del = makeToolChoiceItem("tool_del", TOOL_DEL, L"Delete", L"tools_choice_tool_del");
	p_tools_choice->addComponent(tool_choice_del);
	
	/* 2.1.1 create and add the pens sub heading and options to the choice
	   group */

	p_component_t label_tools_pens = std::make_unique<StaticLabel>(
		"label_tools_pens",
		L"Pens",
		"ui_panel_sub_header"
	);
	label_tools_pens->setTextColour(AppData::UI_PANEL_SUB_HEADING);

	p_tools_choice->addVerticalSpace(25);
	p_tools_choice->addComponent(label_tools_pens);
	p_tools_choice->addVerticalSpace(15);

	p_component_t tool_choice_pen_freehand = makeToolChoiceItem("tool_pen_freehand", TOOL_PEN_FREEHAND, L"Freehand", L"tools_choice_tool_pen_freehand");
	p_tools_choice->addComponent(tool_choice_pen_freehand);
	p_tools_choice->addVerticalSpace(15);

	p_component_t tool_choice_pen_line = makeToolChoiceItem("tool_pen_line", TOOL_PEN_LINE, L"Line", L"tools_choice_tool_pen_line");
	p_tools_choice->addComponent(tool_choice_pen_line);

	/* 2.1.2 create and add the shapes sub heading and options */

	p_component_t label_tools_shapes = std::make_unique<StaticLabel>(
		"label_tools_shapes",
		L"Shapes",
		"ui_panel_sub_header"
	);
	label_tools_shapes->setTextColour(AppData::UI_PANEL_SUB_HEADING);

	p_tools_choice->addVerticalSpace(25);
	p_tools_choice->addComponent(label_tools_shapes);
	p_tools_choice->addVerticalSpace(15);

	p_component_t tool_choice_shape_tri = makeToolChoiceItem("tool_shape_tri", TOOL_SHAPE_TRI, L"Triangle", L"tools_choice_tool_shape_tri");
	p_tools_choice->addComponent(tool_choice_shape_tri);
	p_tools_choice->addVerticalSpace(15);

	p_component_t tool_choice_shape_rect = makeToolChoiceItem("tool_shape_rect", TOOL_SHAPE_RECT, L"Rectangle", L"tools_choice_tool_shape_rect");
	p_tools_choice->addComponent(tool_choice_shape_rect);
	p_tools_choice->addVerticalSpace(15);

	p_component_t tool_choice_shape_circle = makeToolChoiceItem("tool_shape_circle", TOOL_SHAPE_CIRLCE, L"Circle", L"tools_choice_tool_shape_circle");
	p_tools_choice->addComponent(tool_choice_shape_circle);
	p_tools_choice->addVerticalSpace(15);

	p_component_t tool_choice_shape_star = makeToolChoiceItem("tool_shape_star", TOOL_SHAPE_STAR, L"Star", L"tools_choice_tool_shape_star");
	p_tools_choice->addComponent(tool_choice_shape_star);


	/* 3. add the created components to the panel */

	p_panel->addVerticalSpace(25);
	p_panel->addComponent(label_tools);
	p_panel->addVerticalSpace(25);
	p_panel->addComponent(tools_choice);


	/* final: add the group to the ui */

	addComponent(panel);
}

void paint_tool::PaintTool::createRightPanel() {

	/* create the group for the panel */

	p_component_t panel = std::make_unique<ComponentGroup>(
		"right_panel",
		true // fill background
	);
	ComponentGroup *p_panel = dynamic_cast<ComponentGroup *>(panel.get());
	p_panel->setMinimumSize(SIZE{ 260, 800 });
	p_panel->setLayoutStrategy(LAYOUT_VERTICAL);

	p_panel->setBgColour(AppData::UI_PANEL_BG);
	p_panel->setTextColour(AppData::UI_PANEL_TEXT);
	p_panel->setLineColour(AppData::UI_PANEL_BG);


	/* the x coordinate of each group within the panel */

	const int left_margin = 30;


	/* create the selected drawing heading label */

	p_component_t label_tools = std::make_unique<StaticLabel>(
		"right_panel_label_selected",
		L"Selected Drawing",
		"ui_panel_header"
		);
	label_tools->setPosition(POINT{ left_margin, 0 });
	label_tools->setTextColour(AppData::UI_PANEL_HEADING);


	/* create the selected drawing ui */

	p_component_t selected_drawing = std::make_unique<UISelectedDrawing>();
	selected_drawing->setPosition(POINT{ left_margin, 0 });

	/* add components to the group */

	p_panel->addVerticalSpace(25);
	p_panel->addComponent(label_tools);
	p_panel->addVerticalSpace(25);
	p_panel->addComponent(selected_drawing);

	/* add the panel to the ui */

	addComponent(panel);
}

paint_tool::p_component_t paint_tool::PaintTool::makeToolChoiceItem(
	const	std::string		&id,
			ToolChoice		value,
	const	std::wstring	&text,
	const	std::wstring	&icon
) {

	p_component_t tool_choice = std::make_unique<ToolChoiceItem>(
		id, value, text, icon, "ui_panel_body"
	);

	ComponentGroup *group =
		dynamic_cast<ComponentGroup *>(tool_choice.get());

	group->setMinimumSize(SIZE{ 200, 40 });

	tool_choice->setBgColour(AppData::UI_PANEL_ACTIVE, COMPONENT_STATE_ACTIVE);
	tool_choice->setBgColour(AppData::UI_PANEL_FOCUS, COMPONENT_STATE_FOCUSED);
	tool_choice->setBgColour(AppData::UI_PANEL_HOVER, COMPONENT_STATE_HOVERED);

	tool_choice->setLineColour(AppData::UI_PANEL_ACTIVE, COMPONENT_STATE_FOCUSED);
	tool_choice->setLineColour(AppData::UI_PANEL_ACTIVE, COMPONENT_STATE_CHOSEN);
	tool_choice->setLineThickness(2, COMPONENT_STATE_FOCUSED);
	tool_choice->setLineThickness(2, COMPONENT_STATE_CHOSEN);

	return tool_choice;
}