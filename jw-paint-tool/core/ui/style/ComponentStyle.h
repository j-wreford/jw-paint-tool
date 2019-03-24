#pragma once

#include <Windows.h>
#include <string>

#include "core\enum\ComponentStateEnum.h"

//
// ComponentStyle.
//
// A Style describes how to modify the brush when a Component is being drawn.
//
// The StyleManager will chose which StyleSet to get depending on the
// Component's state.
//
// If a particular property within a StyleSet hasn't been set, then this
// property is skipped when the StyleManager is setting colours, making the
// colour used be the last one set. This effectively means that whatever colours
// the Component's parent used will be passed on to the current Component.
//

namespace paint_tool {

	class ComponentStyle {
	public:

		ComponentStyle();
		~ComponentStyle();

		//
		// The structure for a single set of styles.
		//
		// These properties are all pointers to make it obvious when
		// one hasn't been set. NULL cannot be used since 0x0 is a valid
		// colour.
		//
		struct StyleSet {

			inline ~StyleSet() {
				delete text_colour;
				delete bg_colour;
				delete line_colour;
				delete line_thickness;
			}

			//
			// The colour of drawn text
			//
			COLORREF *text_colour = nullptr;

			//
			// The background colour used when drawing shapes
			//
			COLORREF *bg_colour = nullptr;

			//
			// The colour of lines
			//
			COLORREF *line_colour = nullptr;

			//
			// The thickness of lines
			//
			int *line_thickness = nullptr;
		};

		//
		// Returns the StyleSet for the given state
		//
		inline const StyleSet *getStyleSet(ComponentState state) const;
		inline StyleSet *getStyleSet(ComponentState state);

		//
		// Sets the StyleSet for the given state
		//
		inline void setStyleSet(StyleSet *style_set, ComponentState state);

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