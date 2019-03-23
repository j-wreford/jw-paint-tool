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
		L"Hello, world!",
		"test_style",
		"large_font"
		);
	test_label->setPosition(POINT{ 50,50 });
	addComponent(test_label);

	paint_tool::p_component_t test_label_2 = std::make_unique<StaticLabel>(
		"test_label_2",
		L"A label with different font",
		"test_style",
		"small_font"
		);
	test_label_2->setPosition(POINT{ 50, 115 });
	addComponent(test_label_2);

	paint_tool::p_component_t test_box = std::make_unique<StaticBox>(
		"test_box",
		SIZE{ 50, 25 },
		"test_style"
		);
	test_box->setPosition(POINT{ 150, 500 });
	addComponent(test_box);

	// Add a group
	paint_tool::p_component_t test_group_c = std::make_unique<ComponentGroup>(
		"test_group",
		"default",
		false // transparent background
	);
	test_group_c->setPosition(POINT{ 500, 150 });

	// Cast the group to ComponentGroup* so we can call addComponent()
	ComponentGroup *test_group = dynamic_cast<ComponentGroup *>(test_group_c.get());
	//test_group->setDraggable(true); 

	// Add a box to the group
	paint_tool::p_component_t test_box_group = std::make_unique<StaticBox>(
		"test_box_group",
		SIZE{ 15, 25 },
		"test_style_2"
		);
	test_box_group->setPosition(POINT{ 200, 200 });
	test_group->addComponent(test_box_group);

	// Add another box to the group
	paint_tool::p_component_t group_box_2 = std::make_unique<StaticBox>(
		"test_box_group_2",
		SIZE{ 15, 25 },
		"test_style"
		);
	group_box_2->setPosition(POINT{ 0, 200 });
	test_group->addComponent(group_box_2);

	// Add a final box to the group that has negative coords
	paint_tool::p_component_t group_box_3 = std::make_unique<StaticBox>(
		"test_box_group_3",
		SIZE{ 15, 25 },
		"test_style"
		);
	group_box_3->setPosition(POINT{ -30, -50 });
	test_group->addComponent(group_box_3);

	// Add a button to the group
	paint_tool::p_component_t group_btn = std::make_unique<Button>(
		"test_button_in_group",
		SIZE{ 125, 30 },
		L"Test button!",
		"test_style",
		[]() -> void {
			bool a = true;
		}
	);
	group_btn->setPosition(POINT{ -30, 125 });
	test_group->addComponent(group_btn);

	addComponent(test_group_c);

	// Add a test radio group
	paint_tool::p_component_t radio_group =
		std::make_unique<RadioGroup<int>>(
		"radio_group",
		"test_style",
		"small_font"
	);
	radio_group->setPosition(POINT{ 50, 200 });

	RadioGroup<int> *p_radio_group = dynamic_cast<RadioGroup<int> *>(radio_group.get());
	p_radio_group->setLayoutStrategy(LAYOUT_VERTICAL);
	p_radio_group->setMinimumSize(SIZE{ 200, 200 });

	p_radio_group->addChoice(100, "choice_1", L"Choice 1");
	p_radio_group->addHorizontalSpace(10);
	p_radio_group->addChoice(200, "choice_2", L"Choice 2");
	p_radio_group->addHorizontalSpace(10);
	p_radio_group->addChoice(300, "choice_3", L"Choice 3");

	addComponent(radio_group);


	// Build a group which will have a vertical layout


	// Make the group
	paint_tool::p_component_t layout_test_group = std::make_unique<ComponentGroup>(
		"layout_test_group",
		"default",
		false // transparent background
	);
	layout_test_group->setPosition(POINT{ 50, 400 });

	// Cast the group to ComponentGroup* so we can call addComponent()
	ComponentGroup *p_layout_test_group = dynamic_cast<ComponentGroup *>(layout_test_group.get());
	p_layout_test_group->setLayoutStrategy(LAYOUT_VERTICAL);

	// Add some boxes to the group
	for (int i = 0; i < 3; i++) {

		paint_tool::p_component_t layout_test_box = std::make_unique<StaticBox>(
			"layout_test_box_" + std::to_string(i),
			SIZE{ 15, 25 },
			"test_style"
		);
		p_layout_test_group->addComponent(layout_test_box);
		
		if (i < 2)
			p_layout_test_group->addVerticalSpace(10);
	}

	// Add the group
	addComponent(layout_test_group);


	// Make a StaticImage
	p_component_t image = std::make_unique<StaticImage>(
		"image_test",
		SIZE{ 100, 100 },
		L"Elephant"
	);
	image->setPosition(POINT{ 200, 200 });

	addComponent(image);


	InvalidateRect(getHWND(), NULL, false);

	waitForClose();
}

paint_tool::TestUI::~TestUI() {
	//
}