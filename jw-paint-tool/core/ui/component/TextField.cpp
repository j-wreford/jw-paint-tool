#include "TextField.h"

paint_tool::TextField::TextField(
	const	std::string		&id,
	const	SIZE			&size,
	const	std::wstring	&placeholder,
	const	std::string		&font_attr_set_id
) : ValueComponent<std::string>(id, L"") {
	
	
	/* create the box to act as the background */

	p_component_t box = std::make_unique<StaticBox>(
		id + "_text_field_box",
		size
	);


	/* create the label shown when there is a value */

	p_component_t real_label = std::make_unique<StaticLabel>(
		id + "_text_field_real_label",
		L"",
		font_attr_set_id
	);
	real_label->showIf([this]() {
		return getValue().length() > 0;
	});
	

	/* create the placeholder label */

	p_component_t placeholder_label = std::make_unique<StaticLabel>(
		id + "_text_field_placeholder_label",
		placeholder,
		font_attr_set_id
	);
	placeholder_label->showIf([this]() {
		return getValue().length() == 0;
	});
}

paint_tool::TextField::~TextField() {
	//
}

void paint_tool::TextField::onKeyDown(UINT key, UINT flags) {

	std::wstring value = getValue();
	
	/* if the backspace key was pressed, knock off the last character */

	if (key == 0x8 && value.length() > 0) {
		value.pop_back();
		setValue(value);
	}
}

void paint_tool::TextField::onChar(UINT key, UINT flags) {

	char ckey = (char)key;
	wchar_t *wckey = new wchar_t[1];

	MultiByteToWideChar(CP_UTF8, 0, &ckey, sizeof(char), wckey, 1);

	setValue(getValue() += wckey[0]);
}