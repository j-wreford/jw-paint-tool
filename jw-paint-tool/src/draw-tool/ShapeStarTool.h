#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

#include "src\draw-tool\IDrawTool.h"

namespace paint_tool {

	class ShapeStarTool :
		public IDrawTool {
	public:

		ShapeStarTool(Drawing *drawing);
		~ShapeStarTool();

		//
		// Adds 5 points that form a star when traced
		//
		virtual void draw(const POINT & mouse);
	};
}