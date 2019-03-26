#pragma once

#include "core\ui\component\ComponentGroup.h"
#include "src\component\Drawing.h"
#include "src\draw-tool\IDrawTool.h"

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
		virtual void drawComponent(EasyGraphics *ctx) const override;

	private:

		//
		// The current drawing tool
		//
		IDrawTool *draw_tool;
	};
}
