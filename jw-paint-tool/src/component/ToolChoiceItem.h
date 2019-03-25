#pragma once

#include "core\ui\component\ChoiceComponent.h"
#include "core\ui\component\StaticImage.h"
#include "core\ui\component\StaticLabel.h"
#include "src\enum\ToolChoiceEnum.h"

//
// ToolChoiceItem
//
// A tailored RadioItem for the tools choice RadioGroup UI component.
//
//

namespace paint_tool {

	class ToolChoiceItem :
		public ChoiceComponent<ToolChoice> {
	public:

		ToolChoiceItem(
			const	std::string		&id,
					ToolChoice		value,
			const	std::wstring	&text,
			const	std::wstring	&icon,
			const	std::string		&font_attr_set_id = "default"
		);
		~ToolChoiceItem();
	};
}
