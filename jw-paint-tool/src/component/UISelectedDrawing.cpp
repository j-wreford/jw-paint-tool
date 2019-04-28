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


	/* == BEGIN POSITION CONTROLS == */


	/* create the position group */

	p_component_t pos_group = std::make_unique<ComponentGroup>(
		"pos_group"
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


	/* position group sub heading */

	p_component_t pos_heading_label = std::make_unique<StaticLabel>(
		"pos_heading",
		L"Position",
		"ui_panel_sub_header"
	);
	pos_heading_label->setTextColour(AppData::UI_PANEL_SUB_HEADING);
	p_pos_group->addComponent(pos_heading_label);
	p_pos_group->addVerticalSpace(15);


	/* position controls group */

	p_component_t pos_controls_group = std::make_unique<ComponentGroup>(
		"pos_controls_group"
	);
	ComponentGroup *p_pos_controls_group = dynamic_cast<ComponentGroup *>(pos_controls_group.get());
	p_pos_controls_group->setLayoutStrategy(LAYOUT_HORIZONTAL);


	/* position group x group */

	p_component_t pos_x_group = std::make_unique<ComponentGroup>(
		"pos_x_group"
	);
	ComponentGroup *p_pos_x_group = dynamic_cast<ComponentGroup *>(pos_x_group.get());
	p_pos_x_group->setLayoutStrategy(LAYOUT_VERTICAL);


	/* position group x label */

	p_component_t pos_x_label = std::make_unique<StaticLabel>(
		"pos_x_label",
		L"x",
		"ui_panel_body"
	);
	pos_x_label->setTextColour(AppData::UI_PANEL_TEXT);
	p_pos_x_group->addComponent(pos_x_label);
	p_pos_x_group->addVerticalSpace(5);
	

	/* position group x textfield */

	p_component_t pos_x_text_field = std::make_unique<TextField>(
		"pos_x_text_field",
		SIZE{ 0, 25 },
		L"x",
		"ui_panel_body"
	);
	TextField *p_pos_x_text_field = dynamic_cast<TextField *>(pos_x_text_field.get());
	pos_x_text_field->setBgColour(0xffffff);
	pos_x_text_field->setLineThickness(2);
	pos_x_text_field->setLineColour(AppData::UI_PANEL_ACTIVE);
	pos_x_text_field->setTextColour(0x050505);
	p_pos_x_text_field->registerObserver(this);
	p_pos_x_group->addComponent(pos_x_text_field);

	p_pos_controls_group->addComponent(pos_x_group);
	p_pos_controls_group->addHorizontalSpace(20);


	/* position group y group */

	p_component_t pos_y_group = std::make_unique<ComponentGroup>(
		"pos_y_group"
	);
	ComponentGroup *p_pos_y_group = dynamic_cast<ComponentGroup *>(pos_y_group.get());
	p_pos_y_group->setLayoutStrategy(LAYOUT_VERTICAL);


	/* position group y label */

	p_component_t pos_y_label = std::make_unique<StaticLabel>(
		"pos_y_label",
		L"y",
		"ui_panel_body"
	);
	pos_y_label->setTextColour(AppData::UI_PANEL_TEXT);
	p_pos_y_group->addComponent(pos_y_label);
	p_pos_y_group->addVerticalSpace(5);


	/* position group y textfield */

	p_component_t pos_y_text_field = std::make_unique<TextField>(
		"pos_y_text_field",
		SIZE{ 0, 25 },
		L"y",
		"ui_panel_body"
	);
	TextField *p_pos_y_text_field = dynamic_cast<TextField *>(pos_y_text_field.get());
	pos_y_text_field->setBgColour(0xffffff);
	pos_y_text_field->setLineThickness(2);
	pos_y_text_field->setLineColour(AppData::UI_PANEL_ACTIVE);
	pos_y_text_field->setTextColour(0x050505);
	p_pos_y_text_field->registerObserver(this);
	p_pos_y_group->addComponent(pos_y_text_field);

	p_pos_controls_group->addComponent(pos_y_group);

	p_pos_group->addComponent(pos_controls_group);


	/* add the position group */

	p_group->addComponent(pos_group);
	p_group->addVerticalSpace(25);


	/* == END POSITION CONTROLS == */

	/* == BEGIN COLOUR CONTROLS == */


	/* create the colour group */

	p_component_t colours_group = std::make_unique<ComponentGroup>(
		"colour_group"
	);
	colours_group->showIf([]() {

		/* only show this group if the selected drawing has one of (or both)
		   colour properties */

		if (Drawing *drawing = AppData::getInstance()->getDrawingChoice()) {

			auto props = drawing->getProperties();

			return std::any_of(props.begin(), props.end(), [](DrawingProperties prop) {
				return prop == DRAW_PROP_COL_FILL || prop == DRAW_PROP_COL_LINE;
			});
		}
	});
	ComponentGroup *p_colours_group = dynamic_cast<ComponentGroup *>(colours_group.get());
	p_colours_group->setLayoutStrategy(LAYOUT_VERTICAL);


	/* colours group sub heading */

	p_component_t cols_heading_label = std::make_unique<StaticLabel>(
		"colours_heading",
		L"Colours",
		"ui_panel_sub_header"
	);
	cols_heading_label->setTextColour(AppData::UI_PANEL_SUB_HEADING);
	p_colours_group->addComponent(cols_heading_label);
	p_colours_group->addVerticalSpace(15);


	/* fill colour controls group */

	p_component_t fill_col_controls_group = std::make_unique<ComponentGroup>(
		"fill_col_controls_group"
	);
	ComponentGroup *p_fill_col_controls_group = dynamic_cast<ComponentGroup *>(fill_col_controls_group.get());
	p_fill_col_controls_group->setLayoutStrategy(LAYOUT_VERTICAL);
	p_fill_col_controls_group->showIf([]() {

		/* only show the group if the selected drawing can be filled in */

		if (Drawing *drawing = AppData::getInstance()->getDrawingChoice()) {

			auto props = drawing->getProperties();

			return std::any_of(props.begin(), props.end(), [](DrawingProperties prop) {
				return prop == DRAW_PROP_COL_FILL;
			});
		}
	});


	/* fill colour label */

	p_component_t col_fill_label = std::make_unique<StaticLabel>(
		"col_fill_label",
		L"Fill Colour",
		"ui_panel_body"
	);
	p_fill_col_controls_group->addComponent(col_fill_label);
	p_fill_col_controls_group->addVerticalSpace(15);


	/* fill colour control */

	p_component_t col_fill_choice = std::make_unique<ChoiceGroup<int>>(
		"col_fill_choice", 0xffffff
	);
	ChoiceGroup<int> *p_col_fill_choice = dynamic_cast<ChoiceGroup<int> *>(col_fill_choice.get());
	p_col_fill_choice->setLayoutStrategy(LAYOUT_HORIZONTAL);
	p_col_fill_choice->registerObserver(this);

	p_component_t col_choice_red = makeColourChoiceItem("fill_col_red", RGB(0xff, 0x0, 0x0));
	p_col_fill_choice->addComponent(col_choice_red);
	p_col_fill_choice->addHorizontalSpace(15);

	p_component_t col_choice_green = makeColourChoiceItem("fill_col_green", RGB(0x00, 0xff, 0x00));
	p_col_fill_choice->addComponent(col_choice_green);
	p_col_fill_choice->addHorizontalSpace(15);

	p_component_t col_choice_blue = makeColourChoiceItem("fill_col_blue", RGB(0x00, 0x0, 0xff));
	p_col_fill_choice->addComponent(col_choice_blue);
	//p_col_fill_choice->addHorizontalSpace(15);

	p_fill_col_controls_group->addComponent(col_fill_choice);

	p_colours_group->addComponent(fill_col_controls_group);

	p_group->addComponent(colours_group);














	/* colours group line colour group (JUST LABEL FOR NOW) */

	//p_component_t col_line_label = std::make_unique<StaticLabel>(
	//	"right_panel_selected_drawing_col_line_label",
	//	L"Line Colour",
	//	"ui_panel_body"
	//	);
	//col_line_label->showIf([]() {
	//
	//	/* only show the label if the selected drawing has a line colour */
	//
	//	if (Drawing *drawing = AppData::getInstance()->getDrawingChoice()) {
	//
	//		auto props = drawing->getProperties();
	//
	//		return std::any_of(props.begin(), props.end(), [](DrawingProperties prop) {
	//			return prop == DRAW_PROP_COL_LINE;
	//		});
	//	}
	//
	//});
	//p_cols_group->addComponent(col_line_label);
	//
	//p_group->addComponent(cols_group);


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

	/* update the position x textfield value */

	if (Component *pos_x_textfield = getComponent("pos_x_text_field")) {

		POINT pos = component->getPosition();

		dynamic_cast<TextField *>(pos_x_textfield)->setValue(std::to_wstring(pos.x));
	}

	/* update the position y textfield value */

	if (Component *pos_y_textfield = getComponent("pos_y_text_field")) {

		POINT pos = component->getPosition();

		dynamic_cast<TextField *>(pos_y_textfield)->setValue(std::to_wstring(pos.y));
	}

	/* update the fill colour choice value */

	if (Component *col_fill_choice = getComponent("col_fill_choice")) {
		
		const ComponentStyle *style = component->getStyle();

		if (int *colour = style->getBgColour())
			dynamic_cast<ChoiceGroup<int> *>(col_fill_choice)->setValue(*colour);
	}
}

void paint_tool::UISelectedDrawing::update(ValueComponent<std::wstring> *subject) {

	Drawing *drawing = AppData::getInstance()->getDrawingChoice();

	if (subject->getId() == "pos_x_text_field") {

		try {

			int x = std::stoi(subject->getValue());

			drawing->setPosition(
				POINT{
					x,
					drawing->getPosition().y
				}
			);
		}
		catch (const std::exception& e) {
			//
		}
	}

	if (subject->getId() == "pos_y_text_field") {

		try {

			int y = std::stoi(subject->getValue());

			drawing->setPosition(
				POINT{
					drawing->getPosition().x,
					y
				}
			);

		}
		catch (const std::exception& e) {
			//
		}
	}
}

void paint_tool::UISelectedDrawing::update(ValueComponent<int> *subject) {

	Drawing *drawing = AppData::getInstance()->getDrawingChoice();

	if (subject->getId() == "col_fill_choice")
		drawing->setBgColour(subject->getValue());
}

paint_tool::p_component_t paint_tool::UISelectedDrawing::makeColourChoiceItem(
	const	std::string	&id,
	const	int			&value
) {

	p_component_t colour_choice = std::make_unique<ColourChoiceItem>(
		id, SIZE{ 25, 25 }, value
	);

	colour_choice->setLineThickness(2);

	colour_choice->setLineColour(0xffffff, COMPONENT_STATE_CHOSEN);
	

	return colour_choice;
}