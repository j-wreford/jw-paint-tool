#pragma once

#include "src\draw-tool\IDrawTool.h"

namespace paint_tool {

	class ShapeCircleTool :
		public IDrawTool {
	public:

		ShapeCircleTool(Drawing *drawing);
		~ShapeCircleTool();

		//
		// Adds 2 points that are used together to draw a circle.
		//
		// The first point is the center point when drawing the
		// circle.
		//
		// The final point is used to calculate the radius with.
		//
		virtual void draw(const POINT & mouse);
	};
}