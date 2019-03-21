#pragma once

#include "core\ui\component\ComponentGroup.h"
#include "core\ui\component\InternalRadioItem.h"

//
// RadioGroup<ValT>
//
// A radio choice Component.
//

namespace paint_tool {

	template <
		class ValT,
		class ItemComponentT = InternalRadioItem<ValT>
	>
	class RadioGroup :
		public ComponentGroup {
	public:

		inline RadioGroup(
			const	std::string	&id,
			const	POINT		&position,
			const	SIZE		&item_size,
			const   bool		&stack_vertically = true,
			const	std::string &style_set_id = "default"
		);

		inline ~RadioGroup();

		//
		// Adds a choice to the RadioGroup
		//
		inline void addChoice(ValT value);

		//
		// Returns the value of the last clicked InternalRadioItem* within
		// the RadioGroup
		//
		inline ValT getValue() const;

	private:

		//
		// The size of a single ItemComponentT
		//
		SIZE item_size;

		//
		// When true, the ItemComponentT will be stacked vertically on top of
		// each other
		//
		bool stack_vertically;
	};
}

template <class ValT, class ItemComponentT>
paint_tool::RadioGroup<ValT, ItemComponentT>::RadioGroup(
	const	std::string	&id,
	const	POINT		&position,
	const	SIZE		&item_size,
	const   bool		&stack_vertically,
	const	std::string &style_set_id
) :
	ComponentGroup(id, position, style_set_id),
	item_size(item_size),
	stack_vertically(stack_vertically) {
	//
}

template <class ValT, class ItemComponentT>
paint_tool::RadioGroup<ValT, ItemComponentT>::~RadioGroup() {
	//
}

template <class ValT, class ItemComponentT>
void paint_tool::RadioGroup<ValT, ItemComponentT>::addChoice(ValT value) {

	auto items = getChildComponents();

	/* build the id */

	std::string id = getId() + "_choice_" + std::to_string(items->size());

	/* build the position */

	POINT pos = { 0,0 };

	if (stack_vertically)
		pos.y = item_size.cy * items->size();
	else
		pos.x = item_size.cx * items->size();

	p_component_t choice = std::make_unique<ItemComponentT>(
		id,
		pos,
		item_size,
		value,
		getStyleSetId()
		);

	addComponent(choice);
}

template <class ValT, class ItemComponentT>
ValT paint_tool::RadioGroup<ValT, ItemComponentT>::getValue() const {

	ValT value;

	InternalRadioItem *component = getLastActiveComponent();

	if (component) {

		InternalRadioItem<ValT> *choice =
			dynamic_cast<InternalRadioItem<ValT> *>(component);

		if (choice)
			value = choice->getValue();
	}

	return value;
}