#pragma once

#include <Windows.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "core\Singleton.h"
#include "src\component\Canvas.h"

//
// PaintToolFileIO
//
// Provides file input and output using Windows' Common Item Dialog API in order
// to save and load .jwpt files within the application.
//
// Some code here has been adapted from Microsoft's Common Item Dialog
// documentation page. The resource used can be found at the following URL:
// https://msdn.microsoft.com/en-us/library/Bb776913(v=VS.85).aspx#basic_usage
// 
// As a note, I have attempted to comment my understanding of the code I have
// used to show that I am not blindly plagiarising the work!
//

namespace paint_tool {

	class PaintToolFileIO :
		public Singleton<PaintToolFileIO> {
	public:

		friend class Singleton<PaintToolFileIO>;

		//
		// Sets the pointer to the Canvas component used to add Drawing
		// components to (when loading), or to read Drawing properties from
		// (when saving)
		//
		inline void setCanvasPointer(Canvas *_canvas);

		//
		// Performs the neccessary operations to show the open file dialog
		//
		HRESULT showOpenDialog();

		//
		// Performs the neccessary operations to show the save file dialog
		//
		HRESULT showSaveDialog();

	private:

		PaintToolFileIO();
		~PaintToolFileIO();

		//
		// The subject Canvas used during save/load operations
		//
		Canvas *canvas;

		//
		// The allowed file types when opening a file
		//
		static const COMDLG_FILTERSPEC FILE_TYPES[];

		//
		// Opens a file, restricting visible files to those with the .jwpt
		// file extension
		//
		HRESULT open(PCWSTR psz_file_name);

		//
		// Saves the current canvas to the chosen file.
		//
		// Drawing and point information is saved in an XML structure.
		// The following is an example of a single polygon drawing.
		//
		// <drawing type="polygon" pos_x="15" pos_y="15" bg_col="0xffffff" line_col="0xff0000" line_thickness="2">
		//		<point x="10" y="20"/>
		//		<point x="15" y="25"/>
		//		<point x="20" y="30"/>
		// </drawing>
		//
		HRESULT save(PCWSTR psz_file_name);
	};
}

void paint_tool::PaintToolFileIO::setCanvasPointer(Canvas *_canvas) {
	canvas = _canvas;
}