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

	p_component_t id_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_id_label",
		L"Drawing ID: ",
		"ui_panel_body"
	);
	p_group->addComponent(id_label);

	/* create the label displayed when there is no drawing selected */

	p_component_t no_selected_drawing_label = std::make_unique<StaticLabel>(
		"right_panel_selected_drawing_no_select_label",
		L"No drawing selected.",
		"ui_panel_body"
	);
	no_selected_drawing_label->showIf([]() {
		return AppData::getInstance()->getDrawingChoice() == nullptr;
	});


	/* add the components */

	addComponent(group);
	addComponent(no_selected_drawing_label);
}

paint_tool::UISelectedDrawing::~UISelectedDrawing() {
	//
}

void paint_tool::UISelectedDrawing::update(AppData *subject) {
	
	/* update the id label */

	if (Component *id_label = getComponent("right_panel_selected_drawing_id_label")) {

		Component *component = subject->getDrawingChoice();

		if (component) {

			std::string id = component->getId();
			std::wstring w_id(id.begin(), id.end());

			dynamic_cast<StaticLabel *>(id_label)->setText(L"Drawing ID: " + w_id);
		}
		else {
			dynamic_cast<StaticLabel *>(id_label)->setText(L"N/A");
		}
	}
}