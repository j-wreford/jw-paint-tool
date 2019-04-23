#pragma once

#include "core\IObserver.h"
#include "core\ui\component\ComponentGroup.h"

//
// SelectedDrawingGroup
//
//
//

namespace paint_tool {

	class SelectedDrawingGroup :
		public ComponentGroup,
		public IObserver<SelectedDrawingGroup> {
	public:

		SelectedDrawingGroup();
		~SelectedDrawingGroup();
	};
}
