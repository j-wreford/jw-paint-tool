#pragma once

#include "src\component\Drawing.h"

//
// LineDrawing
//
// Draws lines between each point.
//

namespace paint_tool {

	class LineDrawing :
		public Drawing {
	public:

		LineDrawing(const std::string &id);
		~LineDrawing();

		//
		// Draws lines between all its points
		//
		virtual void drawComponent(EasyGraphics *ctx) const override;
	};
}