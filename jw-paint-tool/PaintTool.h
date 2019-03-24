#pragma once

#include "core\ui\Window.h"

//
// PaintTool
//
// The main class for the paint tool application.
//

namespace paint_tool {

	class PaintTool :
		public Window {
	public:

		PaintTool(HINSTANCE hInstance);
		~PaintTool();

	private:

		//
		// Colour constants
		//
		const COLORREF ui_panel_bg;
		const COLORREF ui_panel_text;
		const COLORREF ui_panel_heading;
		const COLORREF ui_panel_sub_heading;

		//
		// Creates all the style sets for use in the application
		//
		void createStyles();

		//
		// Creates all the font sets for use in the application
		//
		void createFonts();

		//
		// Creates the UI components
		//
		void createUI();

		//
		// Creates the drawing canvas
		//
		void createCanvas();

		//
		// Creates the left panel
		//
		void createLeftPanel();
	};
}