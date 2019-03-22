#pragma once

#include "core\ui\component\StaticBox.h"

//
// FixedSpace
//
// This Component is one that isn't drawn, but is used in conjuction
// with the LayoutManager to add spacing between Components.
//

namespace paint_tool {

	class FixedSpace :
		public StaticBox {
	public:

		FixedSpace(
			const	std::string	&id,
			const	SIZE		&size
		);
	
		~FixedSpace();

		//
		// Does nothing
		//
		inline virtual void drawComponent(EasyGraphics *ctx) const override;
	};
}

void paint_tool::FixedSpace::drawComponent(EasyGraphics *ctx) const {
	//
}