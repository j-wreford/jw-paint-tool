#pragma once

#include "src\draw-tool\IDrawTool.h"

namespace paint_tool {

	class ShapeTriTool :
		public IDrawTool {
	public:

		ShapeTriTool(Drawing *drawing);
		~ShapeTriTool();

		//
		// Adds 3 points that form a triangle when traced
		//
		virtual void draw(const POINT & mouse);
	};
}