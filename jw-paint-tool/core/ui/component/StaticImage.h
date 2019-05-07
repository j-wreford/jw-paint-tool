#pragma once

#include <string>

#include "core\ui\component\Component.h"

//
// StaticImage
//
// A Component which loads a bitmap image from file.
//
// The image name given must be inside the resources folder, else the load will
// fail.
//
// Currently, even if the image does not load, the StaticImage still takes up
// space within the user interface.
//

namespace paint_tool {

	class StaticImage :
		public Component {
	public:

		StaticImage(
			const std::string	&id,
			const SIZE			&size,
			const std::wstring	&file_name,
			const int			&transparent = 0xffffff
		);

		~StaticImage();

		//
		// Draws the bitmap
		//
		void drawComponent(EasyGraphics *ctx) const override;

		//
		// Temp: this method will be removed
		//
		inline std::string getComponentType() const override;

		//
		// Returns true when a bmp file with the given name is inside the
		// resources folder
		//
		static bool imageExists(const std::wstring &file_name);

		//
		// Returns the size of the given bmp file.
		//
		// If it does not exist, then the size given will be [-1 x -1].
		//
		static SIZE getImageSize(const std::wstring &file_name);

	private:

		//
		// The name of the bitmap image (omitting the file extension)
		//
		std::wstring file_name;

		//
		// The pixel colour to treat as transparent
		//
		int transparent;

		//
		// Returns the full name of the file by prepending "resources\\" and
		// appending ".bmp"
		//
		static std::wstring getFullName(const std::wstring &file_name);
	};
}

std::string paint_tool::StaticImage::getComponentType() const {
	return "";
}