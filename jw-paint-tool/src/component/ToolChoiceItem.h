#pragma once

#include "core\ui\component\RadioItem.h"
#include "src\enum\ToolChoiceEnum.h"

//
// ToolChoiceItem
//
// A tailored RadioItem for the tools choice RadioGroup UI component.
//
//

namespace paint_tool {

	class ToolChoiceItem :
		public RadioItem<ToolChoice> {

	};
}
