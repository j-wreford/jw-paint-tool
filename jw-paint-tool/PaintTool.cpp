#include "PaintTool.h"

paint_tool::PaintTool::PaintTool(HINSTANCE hInstance) :
	Window(hInstance) {
	
	/* build the user interface here */

	FontManager::getInstance()->addFontAttributeSet("large_font", 50, FW_EXTRALIGHT, false, true, false, "Segoe UI");
	FontManager::getInstance()->addFontAttributeSet("small_font", 20, FW_EXTRALIGHT, false, false, false, "Times New Roman");

	StyleManager::getInstance()->addStyleSet("test_style", 0xf9f9f9, 0xff00ff, 0x00ff00, 1);
	StyleManager::getInstance()->addStyleSet("test_style_2", 0xf9f9f9, 0x45a5ff, 0x4583ff, 1);

	paint_tool::p_component_t test_label = std::make_unique<StaticLabel>(
			"test_label",
			POINT{50, 50},
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
			POINT{150, 500},
			SIZE{50, 25},
			"test_style"
		);
	addComponent(test_box);

	// Add a group
	paint_tool::p_component_t test_group_c = std::make_unique<ComponentGroup>(
		"test_group",
		POINT{500, 150},
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
		SIZE { 15, 25 },
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
		POINT{-30, 125},
		SIZE{ 100, 25 },
		L"Test button!",
		"test_style"
	);
	test_group->addComponent(group_btn);

	addComponent(test_group_c);


	InvalidateRect(getHWND(), NULL, false);

	waitForClose();
}

paint_tool::PaintTool::~PaintTool() {
	//
}