#pragma once

#include <memory>

#include "core\ui\component\ComponentGroup.h"

//
// RootComponent
//
// The root component is a ComponentGroup whose width and height is always the
// width and height of the client rectangle. Its position is always {0, 0}.
//

namespace paint_tool {

	class RootComponent :
		public ComponentGroup {
	public:

		RootComponent(
			const	std::string &style_set_id,
					HWND		h_window
		);
		~RootComponent();

		//
		// Sets the size to the width and height of the client rect
		//
		virtual void recalculateSize() override;

	private:

		//
		// The handle of the EasyGraphics window.
		//
		// Used to calculate the window's width and height.
		//
		HWND h_window;
	};

	typedef std::unique_ptr<RootComponent> p_root_component_t;
}