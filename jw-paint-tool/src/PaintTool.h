#pragma once

#include "core\ui\Window.h"
#include "src\component\Canvas.h"
#include "src\component\ToolChoiceItem.h"
#include "src\component\UISelectedDrawing.h"
#include "src\AppData.h"
#include "src\PaintToolFileIO.h"

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

		virtual void onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override {
			Window::onKeyDown(nChar, nRepCnt, nFlags);

			/* test the file open dialog */

			if (nChar == (UINT) 118) {
				PaintToolFileIO::getInstance()->showOpenDialog();
			}

			/* test the file save dialog */

			if (nChar == (UINT)	119) {
				PaintToolFileIO::getInstance()->showSaveDialog();
			}
		}

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

		//
		// Creates and returns a Button that's to be placed in a UI panel
		//
		p_component_t makeUIButton(
			const	std::string					&id,
			const	std::wstring				&text,
			const	std::function<void(void)>	&callback
		);
	};
}