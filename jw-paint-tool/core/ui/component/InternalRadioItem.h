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

	template <class ValT>
	class InternalRadioItem :
		public InteractiveComponent {
	public:

		InternalRadioItem(
			const	std::string	&id,
			const	POINT		&position,
			const	SIZE		&size,
					ValT		value,
			const	std::string &style_set_id = "default"
		);

		~InternalRadioItem();

		//
		// Draws the radio item
		//
		void drawComponent(EasyGraphics *ctx);

		//
		// Returns the value held by the InternalRadioItem
		//
		ValT getValue() const;

	private:

		//
		// The value of the InternalRadioItem
		//
		ValT value;
	};
}
