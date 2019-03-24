#pragma once

#include <Windows.h>
#include <string>

//
// Style
//
// A Style describes how to modify the brush when a Component is being drawn.
//
// The StyleManager will chose which StyleSet to get depending on the
// Component's state.
//
// If a particular property within a StyleSet hasn't been set, then this
// property is skipped, making the colour used be the last one set. This
// effectively means that whatever colours the Component's parent used will be
// passed on to the current Component.
//
// A Component can have multiple states at once (for example, hovered & active).
// In these cases, the style priority order is:
// active > focused > hovered > normal.
//

namespace paint_tool {

	class Style {
	public:

		Style();
		~Style();

		//
		// The structure for a single set of styles
		//
		struct StyleSet {
			COLORREF *text_colour = nullptr;
			COLORREF *bg_colour = nullptr;
			COLORREF *line_colour = nullptr;
			int *line_thickness = nullptr;
		};

	private:

		//
		// A StyleSet for when the Component is drawn under normal conditions
		//
		StyleSet *normal = new StyleSet;

		//
		// A StyleSet for when the Component is drawn when it's active
		//
		StyleSet *active = new StyleSet;

		//
		// A StyleSet for when the Component is drawn when it's focused
		//
		StyleSet *focused = new StyleSet;

		//
		// A StyleSet for when the Component is drawn when it's hovered
		//
		StyleSet *hovered = new StyleSet;
	};
}