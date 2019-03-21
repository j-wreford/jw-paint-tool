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
		protected ComponentGroup {
	public:

		RadioGroup(
			const	std::string	&id,
			const	POINT		&position,
			const	SIZE		&item_size,
			const   bool		&stack_vertically = true,
			const	std::string &style_set_id = "default"
		);

		~RadioGroup();

		//
		// Adds a choice to the RadioGroup
		//
		void addChoice(const std::string &id, ValT value);

		//
		// Returns the value of the last clicked InternalRadioItem* within
		// the RadioGroup
		//
		ValT getValue() const;

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
