#pragma once

#include <string>

#include "core\ui\component\Component.h"

//
// StaticImage
//
// A Component which loads a bitmap image from file.
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

	private:

		//
		// The name of the bitmap image that's within the resources folder
		//
		std::wstring file_path;

		//
		// The pixel colour to treat as transparent
		//
		int transparent;
	};
}