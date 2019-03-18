#pragma once

#include "core\ui\Window.h"

//
// PaintTool
//
// The main class for the paint tool application.
//

namespace paint_tool {

	class PaintTool :
		public Window {
	public:

		PaintTool(HINSTANCE hInstance);
		~PaintTool();

	private:

		HFONT font_large;
		HFONT font_small;
	};
}