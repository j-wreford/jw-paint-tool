#pragma once

#include "core\ui\Window.h"
#include "src\component\Canvas.h"
#include "src\component\ToolChoiceItem.h"
#include "src\component\UISelectedDrawing.h"
#include "src\AppData.h"

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
		// Creates the left panel, holding the drawing tool option menu
		//
		void createLeftPanel();

		//
		// Creates the right panel, holding the currently select drawing menu
		//
		void createRightPanel();

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