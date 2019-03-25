#pragma once

#include <functional>

#include "core\ui\Component\ComponentGroup.h"
#include "core\ui\Component\StaticBox.h"
#include "core\ui\Component\StaticLabel.h"

//
// Button
//
// A component which reacts to mouse clicks by calling the function given to
// it during construction.
//

namespace paint_tool {

	//
	// The string used to represent the Component
	//
	const std::string CPMNT_BTN = "button";

	class Button :
		public ComponentGroup {
	public:

		Button(
			const	std::string					&id,
			const	SIZE						&size,
			const	std::wstring				&text,
			const	std::function<void(void)>	callback = []() -> bool {}
		);
		~Button();

		//
		// Executes the Button's callback
		//
		virtual void onLeftMouseUpHit(const POINT &mouse) override;

		//
		// Returns true
		//
		inline virtual bool isInteractive() const override;

	private:

		//
		// Upon a successful hit test, this function will be called
		//
		std::function<void(void)> callback;
	};

	typedef std::unique_ptr<Button> p_button_t;
}

bool paint_tool::Button::isInteractive() const {
	return true;
}