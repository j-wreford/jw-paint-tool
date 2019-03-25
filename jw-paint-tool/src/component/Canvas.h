#pragma once

#include "core\ui\component\ComponentGroup.h"

//
// Canvas
//
// The Canvas the user can draw on.
//

namespace paint_tool {

	class Canvas :
		public ComponentGroup {
	public:

		Canvas(const std::string &id);
		~Canvas();

		//
		// Draws the chequered background
		//
		virtual void drawComponent(EasyGraphics *ctx);
	};
}
