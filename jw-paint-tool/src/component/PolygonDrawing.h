#pragma once

#include "src\component\Drawing.h"

//
// PolygonDrawing
//
// Draws a polygon using each point.
//

namespace paint_tool {

	class PolygonDrawing :
		public Drawing {
	public:

		PolygonDrawing(const std::string &id);
		~PolygonDrawing();

		//
		// Draws a polygon using all its points
		//
		virtual void drawComponent(EasyGraphics *ctx) const override;
	};
}