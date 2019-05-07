#pragma once

#include "src\component\Drawing.h"

//
// CircleDrawing
//
// Draws a circle around the given point.
//

namespace paint_tool {

	class CircleDrawing :
		public Drawing {
	public:

		CircleDrawing(const std::string &id);
		~CircleDrawing();

		//
		// Draws lines between all its points
		//
		virtual void drawComponent(EasyGraphics *ctx) const override;
	};
}