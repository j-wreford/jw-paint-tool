#include "RadioGroup.h"

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
void paint_tool::RadioGroup<ValT, ItemComponentT>::addChoice(const std::string &id, ValT value) {

	auto items = getChildComponents();

	/* build the id */

	std::string id = getId() + "_choice_" + items->size();

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
