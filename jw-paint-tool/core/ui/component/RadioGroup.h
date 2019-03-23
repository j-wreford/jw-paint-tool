#pragma once

#include "core\ui\component\ComponentGroup.h"
#include "core\ui\component\RadioItem.h"

//
// RadioGroup<ValT, ItemComponentT<ValT> >
//
// A Component which has the value of one of the added options.
//
// ItemComponentT is the Component used as each individual option component.
// This defaults to RadioItem<ValT>.
//
// If a custom item component is to be used, it must inherit from RadioItem.
//

namespace paint_tool {

	template <class ValT,
			  class ItemComponentT = RadioItem<ValT> >
	class RadioGroup :
		public ComponentGroup {
	public:

		inline RadioGroup(
			const	std::string	&id,
			const	std::string &style_set_id = "default",
			const	std::string &item_font_attr_set_id = "default"
		);

		inline ~RadioGroup();

		//
		// 
		//
		virtual void onLeftMouseButtonDown(const POINT &mouse) override;

		//
		// Adds a choice to the RadioGroup
		//
		inline void addChoice(ValT value, const std::wstring &label);

		//
		// Returns the value of the last clicked InternalRadioItem* within
		// the RadioGroup
		//
		inline ValT getValue() const;

	private:

		//
		// A pointer to the currently selected item 
		//
		RadioItem<ValT> *selected;

		//
		// The font attribute set id to pass down to the radio items
		//
		std::string item_font_attr_set_id;
	};
}

template <class ValT, class ItemComponentT>
paint_tool::RadioGroup<ValT, ItemComponentT>::RadioGroup(
	const	std::string	&id,
	const	std::string &style_set_id,
	const	std::string &item_font_attr_set_id
) :
	ComponentGroup(id, style_set_id),
	selected(nullptr),
	item_font_attr_set_id(item_font_attr_set_id) {
	//
}

template <class ValT, class ItemComponentT>
paint_tool::RadioGroup<ValT, ItemComponentT>::~RadioGroup() {
	//
}

template <class ValT, class ItemComponentT>
void paint_tool::RadioGroup<ValT, ItemComponentT>::onLeftMouseButtonDown(const POINT &mouse) {
	ComponentGroup::onLeftMouseButtonDown(mouse);

	/* bail if the mouse didn't click this radio group */

	if (!wasHit(mouse))
		return;

	/* 1. get the component just clicked by calling getActiveComponent() */

	Component *active_component = getActiveComponent();

	/* 2. check if it is a RadioItem<ValT>* component */

	RadioItem<ValT> *new_selected =
		dynamic_cast<RadioItem<ValT> *>(active_component);

	/* 3. if it is: */

	if (new_selected) {

		/* 3.1 notify the current selected that it's no longer chosen */

		if (selected)
			selected->setChosen(false);

		/* 3.2 set this RadioItem as the new selected */

		selected = new_selected;

		/* 3.3 notify the new active_choice that it's chosen */

		selected->setChosen(true);
	}
}

template <class ValT, class ItemComponentT>
void paint_tool::RadioGroup<ValT, ItemComponentT>::addChoice(ValT value, const std::wstring &label) {

	auto items = getChildComponents();

	/* build the id */

	std::string id = getId() + "_choice_" + std::to_string(items->size());

	p_component_t choice = std::make_unique<ItemComponentT>(
		id,
		value,
		label,
		getStyleSetId(),
		item_font_attr_set_id
	);

	addComponent(choice);
}

template <class ValT, class ItemComponentT>
ValT paint_tool::RadioGroup<ValT, ItemComponentT>::getValue() const {

	ValT value;

	if (selected)
		value = selected->getValue();

	return value;
}