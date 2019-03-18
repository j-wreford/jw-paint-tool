#include "PaintTool.h"

paint_tool::PaintTool::PaintTool(HINSTANCE hInstance) :
	Window(hInstance) {
	
	/* build the user interface here */

	FontManager::getInstance()->addFontAttributeSet("large_font", 50, FW_EXTRABOLD, true, true, true, "Myriad Pro");
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
		POINT{500, 50},
		"default",
		false // transparent background
	);

	// Cast the group to ComponentGroup* so we can call addComponent()
	ComponentGroup *test_group = dynamic_cast<ComponentGroup *>(test_group_c.get());
	test_group->setDraggable(true); 

	// Add a label to the group
	paint_tool::p_component_t group_label = std::make_unique<StaticLabel>(
		"test_label_group",
		POINT{ 10, 0 },
		L"Label within a group!",
		"test_style",
		"small_font"
		);
	test_group->addComponent(group_label);

	// Add a box to the group
	paint_tool::p_component_t test_box_group = std::make_unique<StaticBox>(
		"test_box_group",
		POINT{ 25, 200 },
		SIZE{ 150, 25 },
		"test_style_2"
		);
	test_group->addComponent(test_box_group);

	// Add another label to the group
	paint_tool::p_component_t group_label_2 = std::make_unique<StaticBox>(
		"test_label_group_2",
		POINT{ 0, 300 },
		SIZE { 25, 100 },
		"test_style"
	);
	test_group->addComponent(group_label_2);

	addComponent(test_group_c);


	InvalidateRect(getHWND(), NULL, false);

	waitForClose();
}

paint_tool::PaintTool::~PaintTool() {
	//
}