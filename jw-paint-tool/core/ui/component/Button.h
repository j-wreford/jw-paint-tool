#pragma once

#include <functional>

#include "core\ui\Component\InteractiveComponent.h"

/* TODO: Need an InteractiveComponentGroup class to inherit from instead! 
   The Button component needs to contain a StaticLabel and a StaticBox.
   
   Perhaps a new label class called BoxLabel is needed?
   */

//
// Button
//
// A component which reacts to mouse clicks by calling the function given to
// it during construction.
//

namespace paint_tool {

	class Button :
		public InteractiveComponent {
	public:

		Button();
		~Button();

	private:

		//
		// Upon a successful hit test, this function will be called
		//
		std::function<void> callback;
	};
}
