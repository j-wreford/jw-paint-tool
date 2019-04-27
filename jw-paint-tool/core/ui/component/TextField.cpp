#include "TextField.h"

paint_tool::TextField::TextField(
	const	std::string		&id,
	const	SIZE			&size,
	const	std::wstring	&placeholder,
	const	std::string		&font_attr_set_id
) : ValueComponent<std::wstring>(id, L""),
	placeholder(placeholder) {
	
	setMinimumSize(size);
	setLayoutStrategy(LAYOUT_VERTICAL);
	setFillBackground(true);

	/* create the label shown when there is a value */

	p_component_t real_label = std::make_unique<StaticLabel>(
		id + "_text_field_real_label",
		placeholder, /* initalise the real label with the placeholder text, so that they can be positioned identically */
		font_attr_set_id
	);
	real_label->setPosition(POINT{ 0, 0 });
	real_label->showIf([this]() {
		return getValue().length() > 0;
	});

	/* create the placeholder label */

	p_component_t placeholder_label = std::make_unique<StaticLabel>(
		id + "_text_field_placeholder_label",
		L"  " + placeholder + L"  ",
		font_attr_set_id
	);
	placeholder_label->setPosition(POINT{ 0, 0 });
	placeholder_label->showIf([this]() {
		return getValue().length() == 0;
	});

	/* add the components */

	addVerticalSpace(5);
	addComponent(real_label);
	addComponent(placeholder_label);
	addVerticalSpace(5);
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
		if (Component *tmp = getComponent(getId() + "_text_field_real_label")) {

			if (StaticLabel *label = dynamic_cast<StaticLabel *>(tmp))
				label->setText(L"  " + getValue() + L"  ");
		}
	}

	if (key == 0x20)
		setValue(getValue() += L" ");
}

void paint_tool::TextField::onChar(UINT key, UINT flags) {

	/* bail if this isn't a printable character */

	if (!(key >= 0x21 && key <= 0x7d))
		return;

	char ckey = (char)key;
	wchar_t *wckey = new wchar_t[1];

	MultiByteToWideChar(CP_UTF8, 0, &ckey, sizeof(char), wckey, 1);

	setValue(getValue() += wckey[0]);

	if (Component *tmp = getComponent(getId() + "_text_field_real_label")) {

		if (StaticLabel *label = dynamic_cast<StaticLabel *>(tmp))
			label->setText(L"  " + getValue() + L"  ");
	}
}