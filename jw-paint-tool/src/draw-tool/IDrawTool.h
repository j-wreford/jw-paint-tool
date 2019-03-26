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

		inline IDrawTool(Drawing *drawing, const POINT &mouse);
		inline ~IDrawTool();

		//
		// Manipulates points of the Drawing component
		//
		virtual void draw(const POINT &mouse) = 0;

	protected:

		//
		// Returns the inital mouse down POINT
		//
		inline POINT getInitialMouse() const;

	private:

		//
		// The Drawing component to add point data to
		//
		Drawing *drawing;

		//
		// The POINT of the initial left mouse down
		//
		const POINT initial_mouse;
	};
}

paint_tool::IDrawTool::IDrawTool(Drawing *drawing, const POINT &mouse) :
	drawing(drawing),
	initial_mouse(mouse){
	//
}

paint_tool::IDrawTool::~IDrawTool() {
	//
}

POINT paint_tool::IDrawTool::getInitialMouse() const {
	return initial_mouse;
}