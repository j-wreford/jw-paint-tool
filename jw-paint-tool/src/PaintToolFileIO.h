#pragma once

#include <Windows.h>
#include <shlobj.h>

#include "core\Singleton.h"

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
		// Opens a file, restricting visible files to those with the .jwpt
		// file extension
		//
		void open();

	private:

		PaintToolFileIO();
		~PaintToolFileIO();

		//
		// The allowed file types when opening a file
		//
		static const COMDLG_FILTERSPEC FILE_TYPES[];

		//
		// Performs the neccessary operations to show the open file dialog
		//
		HRESULT showOpenDialog();
	};
}