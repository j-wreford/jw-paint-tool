#pragma once

#include "core\ui\component\ComponentGroup.h"
#include "src\component\Drawing.h"
#include "src\draw-tool\IDrawTool.h"
#include "src\draw-tool\PenFreehandTool.h"
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

		//
		// When there are no Drawings added to the Canvas, it is not considered
		// interactive. As such, the Canvas was never receiving calls to its event
		// methods in order to add Drawings to it.
		//
		// Override this method to always return true.
		//
		inline virtual bool isInteractive() const;

	private:

		//
		// The current drawing tool
		//
		IDrawTool *draw_tool;
	};
}

bool paint_tool::Canvas::isInteractive() const {
	return true;
}