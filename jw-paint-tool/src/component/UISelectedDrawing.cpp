#include "UISelectedDrawing.h"

paint_tool::UISelectedDrawing::UISelectedDrawing() :
	ComponentGroup("right_panel_selected_drawing"),
	selected_drawing(nullptr) {

	setLayoutStrategy(LAYOUT_VERTICAL);

	AppData::getInstance()->registerObserver(this);

	/* create the group to contain various drawing property controls */

	p_component_t group = std::make_unique<ComponentGroup>(
		"right_panel_selected_drawing_controls"
	);

	ComponentGroup *p_group = dynamic_cast<ComponentGroup *>(group.get());
	p_group->setLayoutStrategy(LAYOUT_VERTICAL);
	p_group->showIf([]() {
		return AppData::getInstance()->getDrawingChoice() != nullptr;
	});


	/* create the id label */

	p_component_t id_heading_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_id_heading_label",
		L"Name",
		"ui_panel_sub_header"
		);
	id_heading_label->setTextColour(AppData::UI_PANEL_SUB_HEADING);
	p_group->addComponent(id_heading_label);
	p_group->addVerticalSpace(15);

	p_component_t id_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_id_label",
		L"Drawing ID: ",
		"ui_panel_body"
	);
	p_group->addComponent(id_label);
	p_group->addVerticalSpace(25);


	/* create the position group */

	p_component_t pos_group = std::make_unique<ComponentGroup>(
		"right_panel_selected_drawing_pos_group"
		);
	pos_group->showIf([]() {

		/* only show this group if the selected drawing has the move property */

		if (Drawing *drawing = AppData::getInstance()->getDrawingChoice()) {

			auto props = drawing->getProperties();

			return std::any_of(props.begin(), props.end(), [](DrawingProperties prop) {
				return prop == DRAW_PROP_MOVE;
			});
		}
	});
	ComponentGroup *p_pos_group = dynamic_cast<ComponentGroup *>(pos_group.get());
	p_pos_group->setLayoutStrategy(LAYOUT_VERTICAL);


	/* position group heading */

	p_component_t pos_heading_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_pos_heading_label",
		L"Position",
		"ui_panel_sub_header"
	);
	pos_heading_label->setTextColour(AppData::UI_PANEL_SUB_HEADING);
	p_pos_group->addComponent(pos_heading_label);
	p_pos_group->addVerticalSpace(15);


	/* position group controls (LABEL FOR NOW) */

	p_component_t pos_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_pos_label",
		L"N/A",
		"ui_panel_body"
	);
	p_pos_group->addComponent(pos_label);
	p_pos_group->addVerticalSpace(25);

	p_group->addComponent(pos_group);
	p_group->addVerticalSpace(25);


	/* create the colour group and controls */

	p_component_t cols_group = std::make_unique<ComponentGroup>(
		"right_panel_selected_drawing_cols_group"
	);
	cols_group->showIf([]() {

		/* only show this group if the selected drawing has one of (or both)
		   colour properties */

		if (Drawing *drawing = AppData::getInstance()->getDrawingChoice()) {

			auto props = drawing->getProperties();

			return std::any_of(props.begin(), props.end(), [](DrawingProperties prop) {
				return prop == DRAW_PROP_COL_FILL || prop == DRAW_PROP_COL_LINE;
			});
		}
	});
	ComponentGroup *p_cols_group = dynamic_cast<ComponentGroup *>(cols_group.get());
	p_cols_group->setLayoutStrategy(LAYOUT_VERTICAL);


	/* colours group sub heading */

	p_component_t cols_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_pos_cols_label",
		L"Colours",
		"ui_panel_sub_header"
	);
	cols_label->setTextColour(AppData::UI_PANEL_SUB_HEADING);
	p_cols_group->addComponent(cols_label);
	p_cols_group->addVerticalSpace(15);


	/* colours group fill colour group (JUST LABEL FOR NOW) */

	p_component_t col_fill_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_col_fill_label",
		L"Fill Colour",
		"ui_panel_body"
	);
	col_fill_label->showIf([]() {
	
		/* only show the group if the selected drawing can be filled in */

		if (Drawing *drawing = AppData::getInstance()->getDrawingChoice()) {

			auto props = drawing->getProperties();

			return std::any_of(props.begin(), props.end(), [](DrawingProperties prop) {
				return prop == DRAW_PROP_COL_FILL;
			});
		}
	
	});
	p_cols_group->addComponent(col_fill_label);


	/* colours group line colour group (JUST LABEL FOR NOW) */

	p_component_t col_line_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_col_line_label",
		L"Line Colour",
		"ui_panel_body"
		);
	col_line_label->showIf([]() {

		/* only show the label if the selected drawing has a line colour */

		if (Drawing *drawing = AppData::getInstance()->getDrawingChoice()) {

			auto props = drawing->getProperties();

			return std::any_of(props.begin(), props.end(), [](DrawingProperties prop) {
				return prop == DRAW_PROP_COL_LINE;
			});
		}

	});
	p_cols_group->addComponent(col_line_label);

	p_group->addComponent(cols_group);


	/* create the label displayed when there is no drawing selected */

	p_component_t no_selected_drawing_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_no_select_label",
		L"No drawing selected.",
		"ui_panel_body"
	);
	no_selected_drawing_label->showIf([]() {
		return AppData::getInstance()->getDrawingChoice() == nullptr;
	});
	no_selected_drawing_label->setTextColour(0x909090);

	/* add the components */

	addComponent(group);
	addComponent(no_selected_drawing_label);
}

paint_tool::UISelectedDrawing::~UISelectedDrawing() {
	//
}

void paint_tool::UISelectedDrawing::update(AppData *subject) {

	Component *component = subject->getDrawingChoice();

	if (!component)
		return;
	
	/* update the id label */

	if (Component *id_label = getComponent("right_panel_selected_drawing_id_label")) {

		std::string id = component->getId();
		std::wstring w_id(id.begin(), id.end());

		dynamic_cast<StaticLabel *>(id_label)->setText(w_id);
	}

	/* update the position label */

	if (Component *pos_label = getComponent("right_panel_selected_drawing_pos_label")) {

		POINT pos = component->getPosition();

		dynamic_cast<StaticLabel *>(pos_label)->setText(L"x: " + std::to_wstring(pos.x) + L", y: " + std::to_wstring(pos.y));
	}
}