#pragma once

#include "core\ui\Window.h"
#include "src\component\ToolChoiceItem.h"

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
		static const COLORREF ui_panel_bg;
		static const COLORREF ui_panel_text;
		static const COLORREF ui_panel_heading;
		static const COLORREF ui_panel_sub_heading;
		static const COLORREF ui_panel_active;
		static const COLORREF ui_panel_focus;
		static const COLORREF ui_panel_hover;

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

		//
		// Creates and returns a ToolChoiceItem unique pointer
		//
		p_component_t makeToolChoiceItem(
			const	std::string		&id,
					ToolChoice		value,
			const	std::wstring	&text,
			const	std::wstring	&icon
		);
	};
}