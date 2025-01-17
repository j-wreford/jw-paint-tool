#pragma once

#include "core\ui\Window.h"
#include "core\ui\component\RadioChoice.h"
//
// TestUI
//
// A Window to test various UI components.
//

namespace paint_tool {

	class TestUI :
		public Window {
	public:

		TestUI(HINSTANCE hInstance);
		~TestUI();
	};
}

