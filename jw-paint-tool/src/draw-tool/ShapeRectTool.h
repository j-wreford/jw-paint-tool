#pragma once

#include "src\draw-tool\IDrawTool.h"

namespace paint_tool {

	class ShapeRectTool :
		public IDrawTool {
	public:

		ShapeRectTool(Drawing *drawing);
		~ShapeRectTool();

		//
		// Adds 5 points that form a rectangle when traced
		//
		virtual void draw(const POINT & mouse);
	};
}