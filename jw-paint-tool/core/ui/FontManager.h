#pragma once

#include <Windows.h>
#include <string>
#include <map>

#include "core\Singleton.h"

//
// FontManager
//
// A singleton class which manages fonts for the application.
//
// Internaly is a map of font attrribute set ids to their attribute structures
// (LOGFONT).
//
// Whenever the program requires a font resourse (HFONT), it simply includes
// this header file and calls the getFontHandle() method, supplying the id
// used to add an attribute set with.
//
// The need for this class arose when a Label's font handle was getting deleted
// when a further call to EasyGraphics::setHDEFFont() was made. Subsequent draws
// rendered text in the default monospace font, as the original resource wasn't
// available.
//
// This class aims to avoid this issue by creating a font resource out of a
// given attribute set each time a call to EasyGraphics::setHDEFFont() is
// required. This means that at any one time, there is only one HFONT resource.
//
// Having a font manager class also allows for a font attrribute set to be
// updated and have it replicate across the application.
//

namespace paint_tool {

	class FontManager :
		public Singleton<FontManager> {
	public:

		friend class Singleton<FontManager>;

		//
		// Adds a LOGFONT structure to the font attributes map
		//
		void addFontAttributeSet(
			const	std::string &font_attr_set_id,
			const	int			&height,
			const	int			&weight,
			const	bool		&italic,
			const	bool		&underline,
			const	bool		&strikeout,
			const	std::string &font_face
		);

		//
		// Returns the handle to the created HFONT, using attributes with the
		// given attribute set id.
		//
		// If no font attribuet set was found, then the default one is used.
		//
		HFONT getFontHandle(const std::string &font_attr_set_id);

	private:

		FontManager();
		~FontManager();

		//
		// A map of font attributes
		//
		std::map<std::string, LOGFONT *> font_attr_map;
	};
}
