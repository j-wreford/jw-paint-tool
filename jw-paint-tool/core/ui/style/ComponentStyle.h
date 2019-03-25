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
// A Style describes how to modify the brush when a Component is being drawn,
// depending on its ComponentState.
//
// Any unset properties within the StyleSet returned from calling
// getEffectiveStyleSet will be inherited from the component hierarchy.
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
		// Updates and returns the effective styleset, which is the combination
		// StyleSet of the normal and given state
		//
		const StyleSet *getEffectiveStyleSet(ComponentState state);

		//
		// Sets the corresponding style property for the given component state.
		//
		// If state is not given, then the default style set is updated.
		//
		inline void setTextColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setBgColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setLineColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setLineThickness(const int &thickness, ComponentState state = COMPONENT_STATE_NORMAL);

	private:

		//
		// A map of StyleSets belonging to a certain ComponentState
		//
		std::unordered_map<ComponentState, std::unique_ptr<StyleSet> > state_styleset_map;

		//
		// The StyleSet object that's the result of a merge between the
		// stylesets of the default and the most recently requested state, with
		// the requested state styleset taking priority.
		//
		// For example:
		//
		// NORMAL STATE         REQUESTED STATE          RETURN STATE
		// ------------         ---------------          ------------
		// bg_colour  0xffffff  bg_colour      0x000000  bg_color       0x000000
		// text_color 0x000000  text_colour    0xffffff  text_color     0xffffff
		// line_color 0x0000ff                           line_color     0x0000ff
		//                      line_thickness 2         line_thickness 2
		//
		// This property is updated every time getEffectiveStyleSet is called.
		//
		std::unique_ptr<StyleSet> effective_styleset;
	};
}

void paint_tool::ComponentStyle::setTextColour(const int &colour, ComponentState state) {
	state_styleset_map[state]->text_colour = std::make_unique<int>(colour);
}

void paint_tool::ComponentStyle::setBgColour(const int &colour, ComponentState state) {
	state_styleset_map[state]->bg_colour = std::make_unique<int>(colour);
}

void paint_tool::ComponentStyle::setLineColour(const int &colour, ComponentState state) {
	state_styleset_map[state]->line_colour = std::make_unique<int>(colour);
}

void paint_tool::ComponentStyle::setLineThickness(const int &thickness, ComponentState state) {
	state_styleset_map[state]->line_thickness = std::make_unique<int>(thickness);
}