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
			const std::wstring	&file_path,
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

	private:

		//
		// The name of the bitmap image (omitting the file extension)
		//
		std::wstring file_path;

		//
		// The pixel colour to treat as transparent
		//
		int transparent;
	};
}

std::string paint_tool::StaticImage::getComponentType() const {
	return "";
}