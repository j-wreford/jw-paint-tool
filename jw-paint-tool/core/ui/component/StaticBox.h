#pragma once

#include "core\ui\component\Component.h"

//
// StaticBox
//
// A simple component which will draw a rectangle to the screen.
//

namespace paint_tool {

	//
	// The string used to represent the Component
	//
	const std::string CPMNT_STATIC_BOX = "static_box";

	class StaticBox :
		public Component {
	public:

		StaticBox(
			const	std::string	&id,
			const	SIZE		&size,
			const	std::string &style_set_id = "default"
		);
		~StaticBox();

		//
		// Draws a filled in rectangle to the given EasyGraphics context
		//
		virtual void drawComponent(EasyGraphics *ctx) const override;

		//
		// Returns CPMNT_STATIC_BOX
		//
		inline virtual std::string getComponentType() const override;
	};
}

std::string paint_tool::StaticBox::getComponentType() const {
	return CPMNT_STATIC_BOX;
}