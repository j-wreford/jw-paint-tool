#pragma once

#include <Windows.h>

#include "src\component\Drawing.h"

//
// IDrawTool
//
// An interface for the different types of drawing tools to implement.
//

namespace paint_tool {

	class IDrawTool {
	protected:

		inline IDrawTool(Drawing *drawing);
		inline ~IDrawTool();

		virtual void respondToLeftMouseDown(const POINT & mouse) = 0;
		virtual void respondToLeftMouseUp(const POINT & mouse) = 0;
		virtual void respondToMouseMove(const POINT &mouse) = 0;

	private:

		//
		// The Drawing component to add point data to
		//
		Drawing *drawing;
	};
}

paint_tool::IDrawTool::IDrawTool(Drawing *drawing) :
	drawing(drawing) {
	//
}

paint_tool::IDrawTool::~IDrawTool() {
	//
}