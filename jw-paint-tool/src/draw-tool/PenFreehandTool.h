#pragma once

#include "src\draw-tool\IDrawTool.h"

namespace paint_tool {

	class PenFreehandTool :
		public IDrawTool {
	public:

		PenFreehandTool(Drawing *drawing);
		~PenFreehandTool();

		//
		// Adds the new mouse point to the Drawing's point list
		//
		virtual void draw(const POINT & mouse);
	};
}