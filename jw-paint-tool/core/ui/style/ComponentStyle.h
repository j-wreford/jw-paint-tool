#pragma once

#include <Windows.h>
#include <memory>
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

			//
			// The colour of drawn text
			//
			std::unique_ptr<int> text_colour = nullptr;

			//
			// The background colour used when drawing shapes
			//
			std::unique_ptr<int> bg_colour = nullptr;

			//
			// The colour of lines
			//
			std::unique_ptr<int> line_colour = nullptr;

			//
			// The thickness of lines
			//
			std::unique_ptr<int> line_thickness = nullptr;
		};

		//
		// Returns the StyleSet for the given state
		//
		const StyleSet *getStyleSet(ComponentState state) const;
		StyleSet *getStyleSet(ComponentState state);

		//
		// Sets the StyleSet for the given state
		//
		void setStyleSet(StyleSet *style_set, ComponentState state);

	private:

		//
		// A StyleSet for when the Component is drawn under normal conditions
		//
		std::unique_ptr<StyleSet> normal = std::make_unique<StyleSet>();

		//
		// A StyleSet for when the Component is drawn when it's active
		//
		std::unique_ptr<StyleSet> active = std::make_unique<StyleSet>();

		//
		// A StyleSet for when the Component is drawn when it's focused
		//
		std::unique_ptr<StyleSet> focused = std::make_unique<StyleSet>();

		//
		// A StyleSet for when the Component is drawn when it's hovered
		//
		std::unique_ptr<StyleSet> hovered = std::make_unique<StyleSet>();
	};
}