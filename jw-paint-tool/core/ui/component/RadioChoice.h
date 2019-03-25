#pragma once

#include "core\ui\component\ChoiceComponent.h"

//
// RadioChoice
//
// A very simple ChoiceComponent which is a circle that gets filled in when
// chosen. Primarily used for testing ChoiceGroup.
//

namespace paint_tool {

	template <typename T>
	class RadioChoice :
		public ChoiceComponent<T> {
	public:

		RadioChoice(const std::string &id, T default_value);
		~RadioChoice();

		//
		// Draws the radio component
		//
		virtual void drawComponent(EasyGraphics *ctx) const;
	};
}

template <class T>
paint_tool::RadioChoice<T>::RadioChoice(const std::string &id, T default_value) :
	ChoiceComponent(id, default_value) {
	//
}

template <class T>
paint_tool::RadioChoice<T>::~RadioChoice() {
	//
}

template <class T>
void paint_tool::RadioChoice<T>::drawComponent(EasyGraphics *ctx) const {

	POINT pos = getAbsolutePosition();

	POINT center = {
		pos.x + (getSize().cx / 2),
		pos.y + (getSize().cy / 2)
	};

	ctx->drawCircle(center.x, center.y, (getSize().cx / 2), false);

	if (isChosen())
		ctx->drawCircle(center.x, center.y, (getSize().cx / 4), true);
}