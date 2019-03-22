#include "TestUI.h"

paint_tool::TestUI::TestUI(HINSTANCE hInstance) :
	Window(hInstance) {

	/* build the user interface here */

	FontManager::getInstance()->addFontAttributeSet("large_font", 50, FW_THIN, false, true, false, "Segoe UI");
	FontManager::getInstance()->addFontAttributeSet("small_font", 20, FW_THIN, false, false, false, "Times New Roman");

	StyleManager::getInstance()->addStyleSet("test_style", 0xf9f9f9, 0xff00ff, 0x00ff00, 1);
	StyleManager::getInstance()->addStyleSet("test_style_2", 0xf9f9f9, 0x45a5ff, 0x4583ff, 1);

	paint_tool::p_component_t test_label = std::make_unique<StaticLabel>(
		"test_label",
		POINT{ 50, 50 },
		L"Hello, world!",
		"test_style",
		"large_font"
		);
	addComponent(test_label);

	paint_tool::p_component_t test_label_2 = std::make_unique<StaticLabel>(
		"test_label_2",
		POINT{ 50, 115 },
		L"A label with different font",
		"test_style",
		"small_font"
		);
	addComponent(test_label_2);

	paint_tool::p_component_t test_box = std::make_unique<StaticBox>(
		"test_box",
		POINT{ 150, 500 },
		SIZE{ 50, 25 },
		"test_style"
		);
	addComponent(test_box);

	// Add a group
	paint_tool::p_component_t test_group_c = std::make_unique<ComponentGroup>(
		"test_group",
		POINT{ 500, 150 },
		"default",
		false // transparent background
		);

	// Cast the group to ComponentGroup* so we can call addComponent()
	ComponentGroup *test_group = dynamic_cast<ComponentGroup *>(test_group_c.get());
	//test_group->setDraggable(true); 

	// Add a box to the group
	paint_tool::p_component_t test_box_group = std::make_unique<StaticBox>(
		"test_box_group",
		POINT{ 200, 200 },
		SIZE{ 15, 25 },
		"test_style_2"
		);
	test_group->addComponent(test_box_group);

	// Add another box to the group
	paint_tool::p_component_t group_box_2 = std::make_unique<StaticBox>(
		"test_box_group_2",
		POINT{ 0, 200 },
		SIZE{ 15, 25 },
		"test_style"
		);
	test_group->addComponent(group_box_2);

	// Add a final box to the group that has negative coords
	paint_tool::p_component_t group_box_3 = std::make_unique<StaticBox>(
		"test_box_group_3",
		POINT{ -30, -50 },
		SIZE{ 15, 25 },
		"test_style"
		);
	test_group->addComponent(group_box_3);

	// Add a button to the group
	paint_tool::p_component_t group_btn = std::make_unique<Button>(
		"test_button_in_group",
		POINT{ -30, 125 },
		SIZE{ 125, 30 },
		L"Test button!",
		"test_style",
		[]() -> void {
		bool a = true;
	}
	);
	test_group->addComponent(group_btn);

	addComponent(test_group_c);

	// Add a test radio group
	paint_tool::p_component_t radio_group = std::make_unique<RadioGroup<int>>(
		"radio_group",
		POINT{ 50, 200 },
		SIZE{ 25, 25 },
		true, // stack vertically
		"test_style"
		);

	RadioGroup<int> *p_radio_group = dynamic_cast<RadioGroup<int> *>(radio_group.get());
	p_radio_group->addChoice(100);
	p_radio_group->addChoice(200);
	p_radio_group->addChoice(300);

	addComponent(radio_group);


	// Build a group which will have a vertical layout


	// Make the group
	paint_tool::p_component_t layout_test_group = std::make_unique<ComponentGroup>(
		"layout_test_group",
		POINT{ 50, 400 },
		"default",
		false // transparent background
	);

	// Cast the group to ComponentGroup* so we can call addComponent()
	ComponentGroup *p_layout_test_group = dynamic_cast<ComponentGroup *>(layout_test_group.get());
	p_layout_test_group->setLayoutStrategy(LAYOUT_VERTICAL);

	// Add some boxes to the group
	for (int i = 0; i < 3; i++) {

		paint_tool::p_component_t layout_test_box = std::make_unique<StaticBox>(
			"layout_test_box_" + std::to_string(i),
			POINT{ 0, 0 },
			SIZE{ 15, 25 },
			"test_style"
		);
		p_layout_test_group->addComponent(layout_test_box);
	}

	// Add the group
	addComponent(layout_test_group);



	InvalidateRect(getHWND(), NULL, false);

	waitForClose();
}

paint_tool::TestUI::~TestUI() {
	//
}