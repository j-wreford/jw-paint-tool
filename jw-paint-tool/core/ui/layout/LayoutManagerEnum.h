#pragma once

namespace paint_tool {

	//
	// Determines the layout mode
	//
	enum LayoutStrategy {
		LAYOUT_VERTICAL,
		LAYOUT_HORIZONTAL
	};

	//
	// Determines how Components within a layout mode are aligned
	//
	enum AlignStrategy {
		ALIGN_LEFT_OR_TOP,
		ALIGN_MIDDLE,
		ALIGN_RIGHT_OR_BOTTOM
	};
}
