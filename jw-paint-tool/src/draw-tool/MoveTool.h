#pragma once

#include "src\draw-tool\IDrawTool.h"

namespace paint_tool {

	class MoveTool :
		public IDrawTool {
	public:

		MoveTool(Drawing *drawing);
		~MoveTool();

		//
		// Adjusts the position of the Drawing component
		//
		virtual void draw(const POINT & mouse);
	};
}