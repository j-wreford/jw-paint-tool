#include "TestUI.h"

paint_tool::TestUI::TestUI(HINSTANCE hInstance) :
	Window(hInstance) {

	/* build the user interface here */

	FontManager::getInstance()->addFontAttributeSet("large_font", 50, FW_THIN, false, true, false, "Segoe UI");
	FontManager::getInstance()->addFontAttributeSet("small_font", 20, FW_THIN, false, false, false, "Times New Roman");


	ComponentGroup *root = getRootComponent();
	root->setBgColour(0xffffff);
	root->setTextColour(0x101010);
	root->setLineColour(0xc0c0c0);
	root->setLineThickness(2);



	p_component_t text_field = std::make_unique<TextField>(
		"text_field",
		SIZE{ 150, 40 },
		L"Textfield placeholder!",
		"small_font"
	);
	text_field->setPosition(POINT{ 0, 0 });
	text_field->setBgColour(0xe9e9e9);
	dynamic_cast<ComponentGroup *>(text_field.get())->setMinimumSize(SIZE{ 150, 40 });
	addComponent(text_field);



	paint_tool::p_component_t test_label = std::make_unique<StaticLabel>(
		"test_label",
		L"Hello, world!",
		"large_font"
		);
	test_label->setPosition(POINT{ 50,50 });
	addComponent(test_label);

	paint_tool::p_component_t test_label_2 = std::make_unique<StaticLabel>(
		"test_label_2",
		L"A label with different font",
		"small_font"
	);
	test_label_2->setPosition(POINT{ 50, 115 });
	addComponent(test_label_2);

	paint_tool::p_component_t test_box = std::make_unique<StaticBox>(
		"test_box",
		SIZE{ 50, 25 }
	);
	test_box->setPosition(POINT{ 150, 500 });
	addComponent(test_box);

	// Add a group
	paint_tool::p_component_t test_group_c = std::make_unique<ComponentGroup>(
		"test_group",
		false // transparent background
	);
	test_group_c->setPosition(POINT{ 500, 150 });

	// Cast the group to ComponentGroup* so we can call addComponent()
	ComponentGroup *test_group = dynamic_cast<ComponentGroup *>(test_group_c.get());
	//test_group->setDraggable(true); 

	// Add a box to the group
	paint_tool::p_component_t test_box_group = std::make_unique<StaticBox>(
		"test_box_group",
		SIZE{ 15, 25 }
	);
	test_box_group->setPosition(POINT{ 200, 200 });
	test_group->addComponent(test_box_group);

	// Add another box to the group
	paint_tool::p_component_t group_box_2 = std::make_unique<StaticBox>(
		"test_box_group_2",
		SIZE{ 15, 25 }
	);
	group_box_2->setPosition(POINT{ 0, 200 });
	test_group->addComponent(group_box_2);

	// Add a final box to the group that has negative coords
	paint_tool::p_component_t group_box_3 = std::make_unique<StaticBox>(
		"test_box_group_3",
		SIZE{ 15, 25 }
	);
	group_box_3->setPosition(POINT{ -30, -50 });
	test_group->addComponent(group_box_3);

	// Add a button to the group
	paint_tool::p_component_t group_btn = std::make_unique<Button>(
		"test_button_in_group",
		SIZE{ 125, 30 },
		L"Test button!",
		[]() -> void {
			bool a = true;
		}
	);
	group_btn->setPosition(POINT{ -30, 125 });
	test_group->addComponent(group_btn);

	addComponent(test_group_c);

	// Add a test radio group

	paint_tool::p_component_t choice_group = std::make_unique<ChoiceGroup<int>>(
		"radio_group",
		9999
	);
	choice_group->setPosition(POINT{ 50, 200 });

	ChoiceGroup<int> *p_choice_group = dynamic_cast<ChoiceGroup<int> *>(choice_group.get());
	p_choice_group->setLayoutStrategy(LAYOUT_VERTICAL);
	p_choice_group->setMinimumSize(SIZE{ 200, 200 });

	p_component_t choice_group_item_1 = std::make_unique<RadioChoice<int>>("choice_option_1", 100);
	p_choice_group->addComponent(choice_group_item_1);
	//p_choice_group->addChoice(100, "choice_1", L"Choice 1");

	p_choice_group->addHorizontalSpace(10);

	p_component_t choice_group_item_2 = std::make_unique<RadioChoice<int>>("choice_option_2", 200);
	p_choice_group->addComponent(choice_group_item_2);
	//p_choice_group->addChoice(200, "choice_2", L"Choice 2");

	p_choice_group->addHorizontalSpace(10);

	p_component_t choice_group_item_3 = std::make_unique<RadioChoice<int>>("choice_option_3", 300);
	p_choice_group->addComponent(choice_group_item_3);
	//p_choice_group->addChoice(300, "choice_3", L"Choice 3");

	addComponent(choice_group);


	// Build a group which will have a vertical layout


	// Make the group
	paint_tool::p_component_t layout_test_group = std::make_unique<ComponentGroup>(
		"layout_test_group",
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
			SIZE{ 15, 25 }
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