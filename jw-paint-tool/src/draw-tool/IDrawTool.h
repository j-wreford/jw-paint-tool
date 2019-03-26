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
	public:

		inline IDrawTool(Drawing *drawing);
		inline ~IDrawTool();

		//
		// Manipulates points of the Drawing component
		//
		virtual void draw(const POINT &mouse) = 0;

	protected:

		//
		// Returns the pointer to the Drawing component the tool
		// is manipulating
		//
		inline Drawing *getDrawing();

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

paint_tool::Drawing *paint_tool::IDrawTool::getDrawing() {
	return drawing;
}