#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "core\enum\ComponentStateEnum.h"

//
// ComponentStyle.
//
// A Style describes how to modify the brush when a Component is being drawn.
// 
// It is built up of 4 individual StyleSets, each attrributed to a certain
// state of a Component.
//
// Any unset properties within a StyleSet will be inherited from its parent.
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
		// Sets the corresponding style property for the given component state.
		//
		// If state is not given, then the default style set is updated.
		//
		// If the default state is being updated, then the special states will
		// also be updated (if they have not been set before).
		//
		void setTextColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		void setBgColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		void setLineColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		void setLineThickness(const int &thickness, ComponentState state = COMPONENT_STATE_NORMAL);
		void setStyleSet(StyleSet *style_set, ComponentState state);

	private:

		//
		// A map of StyleSets belonging to a certain ComponentState
		//
		std::unordered_map<ComponentState, std::unique_ptr<StyleSet> > state_styleset_map;
	};
}