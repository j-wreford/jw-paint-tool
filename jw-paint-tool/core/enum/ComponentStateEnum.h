#pragma once

namespace paint_tool {

	//
	// Describes the state of a Component
	//
	enum ComponentState {
		COMPONENT_STATE_NORMAL,
		COMPONENT_STATE_ACTIVE,
		COMPONENT_STATE_FOCUSED,
		COMPONENT_STATE_HOVERED,
		COMPONENT_STATE_CHOSEN
	};
}
