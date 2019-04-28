#pragma once

#include "core\ui\component\ChoiceComponent.h"
#include "core\ui\component\StaticBox.h"

namespace paint_tool {

	class ColourChoiceItem :
		public ChoiceComponent<int> {
	public:

		ColourChoiceItem(
			const	std::string	&id,
			const	SIZE		&size,
			const	int			&value
		);
		~ColourChoiceItem();
	};
}