#pragma once

#include "src\draw-tool\IDrawTool.h"

namespace paint_tool {

	class PenLineTool :
		public IDrawTool {
	public:

		PenLineTool(Drawing *drawing);
		~PenLineTool();

		//
		// Sets two points, the first starting on the location of the
		// initial mouse down press, and the last on the current mouse move
		// point
		//
		virtual void draw(const POINT & mouse);
	};
}