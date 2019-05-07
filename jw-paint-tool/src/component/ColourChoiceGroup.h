#pragma once

#include "core\ui\component\ChoiceGroup.h"
#include "src\component\ColourChoiceItem.h"

//
// ColourChoiceGroup
//
// A packaged ChoiceGroup<int> which offers multiple colours to choose from.
//

namespace paint_tool {

	class ColourChoiceGroup :
		public ChoiceGroup<int> {
	public:

		ColourChoiceGroup(const std::string &id, const int &default_col);
		~ColourChoiceGroup();
	
	private:

		//
		// Creates and returns a ColourChoiceItem unique pointer
		//
		p_component_t makeColourChoiceItem(
			const	std::string	&id,
			const	int			&value
		);
	};
}
