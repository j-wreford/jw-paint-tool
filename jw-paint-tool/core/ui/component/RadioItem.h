#pragma once

#include "core\ui\component\ComponentGroup.h"
#include "core\ui\component\StaticLabel.h"
#include "core\ui\component\StaticImage.h"

//
// RadioItem<ValT>
//
// A component to go with a RadioGroup.
//
// This radio item component is a Label which is underlined when selected.
//
// ValT is the data type of the option.
//

namespace paint_tool {

	template <class ValT>
	class RadioItem :
		public ComponentGroup {
	public:

		RadioItem(
			const	std::string		&id,
			ValT					value,
			const	std::wstring	&text,
			const	std::string		&style_set_id = "default",
			const	std::string		&font_attr_set_id = "default"
		);

		~RadioItem();

		//
		// Draws the radio item
		//
		inline virtual void drawComponent(EasyGraphics *ctx) const override;

		//
		// Returns the value held by the RadioItem
		//
		inline ValT getValue() const;

		//
		// Returns true.
		//
		// As ComponentGroup will only return true for this method when at least
		// one of its child components are interactive, we need to override it
		// and just return true (the only component in this group is a label,
		// which is not interactive).
		//
		inline bool isInteractive() const override;

		//
		// Sets chosen.
		//
		// This method should only be called from inside RadioGroup,
		// as calling this method won't actually changed the value of the
		// RadioGroup this RadioItem is contained in.
		//
		inline void setChosen(const bool &_chosen);

	private:

		//
		// The value of the RadioItem
		//
		ValT value;

		//
		// When true, the RadioItem will be underlined when drawn
		//
		bool chosen;

		//
		// The constant ID of the label
		//
		static const std::string LABEL_ID;
	};
}

template <class ValT>
const std::string paint_tool::RadioItem<ValT>::LABEL_ID = "radio_item_label";

template <class ValT>
paint_tool::RadioItem<ValT>::RadioItem(
	const	std::string		&id,
	ValT					value,
	const	std::wstring	&text,
	const	std::string		&style_set_id,
	const	std::string		&font_attr_set_id
) :
	ComponentGroup(id, style_set_id),
	value(value),
	chosen(false){

	/* if there is an image with the same id as this choice, then create a
       static image component */

	std::wstring image_name(id.begin(), id.end());

	if (StaticImage::imageExists(image_name)) {

		p_component_t image = std::make_unique<StaticImage>(
			id + "_img",
			StaticImage::getImageSize(image_name),
			image_name,
			0x00ff00
			);
		addComponent(image);

		setLayoutStrategy(LAYOUT_HORIZONTAL);
	}
	
	/* make the label for this radio item */

	p_component_t label = std::make_unique<StaticLabel>(
		LABEL_ID,
		text,
		style_set_id,
		font_attr_set_id
	);
	addComponent(label);
}

template <class ValT>
paint_tool::RadioItem<ValT>::~RadioItem() {
	//
}

template <class ValT>
void paint_tool::RadioItem<ValT>::drawComponent(EasyGraphics *ctx) const {
	ComponentGroup::drawComponent(ctx);

	if (chosen) {

		RECT rect = getAbsoluteRect();
		ctx->drawLine(rect.left, rect.bottom, rect.right, rect.bottom);
	}
}

template <class ValT>
ValT paint_tool::RadioItem<ValT>::getValue() const {
	return value;
}

template <class ValT>
bool paint_tool::RadioItem<ValT>::isInteractive() const {
	return true;
}

template <class ValT>
void paint_tool::RadioItem<ValT>::setChosen(const bool &_chosen) {
	chosen = _chosen;
}