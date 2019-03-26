#pragma once

#include "core\ui\component\ComponentGroup.h"
#include "src\component\Drawing.h"
#include "src\draw-tool\IDrawTool.h"
#include "src\draw-tool\PenLineTool.h"

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

		//
		// If the current draw_tool is not the move or delete tool,
		// then this method created an empty Drawing component and
		// passes it to the IDrawTool to begin forming a new drawing
		//
		virtual void onLeftMouseDownHit(const POINT &mouse) override;

		//
		// 
		//
		virtual void onLeftMouseUpHit(const POINT &mouse) override;

		//
		// 
		//
		virtual void onMouseMoveHit(const POINT &mouse, const bool& lmouse_down) override;

	private:

		//
		// The current drawing tool
		//
		IDrawTool *draw_tool;
	};
}
