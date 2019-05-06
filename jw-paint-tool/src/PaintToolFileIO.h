#pragma once

#include <Windows.h>
#include <shlobj.h>

#include "core\Singleton.h"

//
// PaintToolFileIO
//
// Provides file input and output using Windows' Common File Dialog API in order
// to save and load .jwpt files within the application.
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
	};
}