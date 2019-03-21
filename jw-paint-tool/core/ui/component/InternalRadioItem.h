#pragma once

#include "core\ui\component\InteractiveComponent.h"

//
// InternalRadioItem<ValT>
//
// A Component which is internal to RadioGroup. For every option added to the
// group, a new InternalRadioItem will be instantiated.
//
// ValT is the data type of the option.
//

namespace paint_tool {

	//
	// The string used to represent the Component
	//
	const std::string CPMNT_INTERNAL_RADIO_ITEM = "interal_radio_item";


	template <class ValT>
	class InternalRadioItem :
		public InteractiveComponent {
	public:

		inline InternalRadioItem(
			const	std::string	&id,
			const	POINT		&position,
			const	SIZE		&size,
					ValT		value,
			const	std::string &style_set_id = "default"
		);

		inline ~InternalRadioItem();

		//
		// Draws the radio item
		//
		inline virtual void drawComponent(EasyGraphics *ctx) const override;

		//
		// Returns CPMNT_INTERNAL_RADIO_ITEM
		//
		inline virtual std::string getComponentType() const override;

		//
		// Returns the value held by the InternalRadioItem
		//
		inline ValT getValue() const;

	private:

		//
		// The value of the InternalRadioItem
		//
		ValT value;
	};
}

template <class ValT>
paint_tool::InternalRadioItem<ValT>::InternalRadioItem(
	const	std::string	&id,
	const	POINT		&position,
	const	SIZE		&size,
	ValT		value,
	const	std::string &style_set_id
) :
	InteractiveComponent(id, position, size, style_set_id),
	value(value) {
	//
}

template <class ValT>
paint_tool::InternalRadioItem<ValT>::~InternalRadioItem() {
	//
}

template <class ValT>
void paint_tool::InternalRadioItem<ValT>::drawComponent(EasyGraphics *ctx) const {

	POINT pos = getAbsolutePosition();

	ctx->setPenColour(0xffffff, 2);
	ctx->selectBackColour(0xffffff);

	POINT center = {
		pos.x + (getSize().cx / 2),
		pos.y + (getSize().cy / 2)
	};

	ctx->drawCircle(center.x, center.y, (getSize().cx / 2), false);

	ComponentGroup *group = dynamic_cast<ComponentGroup *>(getParent());

	if (group->getLastActiveComponent() == this)
			ctx->drawCircle(center.x, center.y, (getSize().cx / 6), true);
}

template <class ValT>
std::string paint_tool::InternalRadioItem<ValT>::getComponentType() const {
	return CPMNT_INTERNAL_RADIO_ITEM;
}

template <class ValT>
ValT paint_tool::InternalRadioItem<ValT>::getValue() const {
	return value;
}