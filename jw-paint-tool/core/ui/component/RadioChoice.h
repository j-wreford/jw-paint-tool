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

		RadioChoice(const std::string &id, T value);
		~RadioChoice();

		//
		// Draws the radio component
		//
		virtual void drawComponent(EasyGraphics *ctx) const override;
	};
}

template <typename T>
paint_tool::RadioChoice<T>::RadioChoice(const std::string &id, T value) :
	ChoiceComponent<T>(id, value) {
	
	this->setSize(SIZE{ 25,25 });
}

template <typename T>
paint_tool::RadioChoice<T>::~RadioChoice() {
	//
}

template <typename T>
void paint_tool::RadioChoice<T>::drawComponent(EasyGraphics *ctx) const {
	
	POINT pos = this->getAbsolutePosition();
	SIZE size = this->getSize();

	POINT center = {
		pos.x + (size.cx / 2),
		pos.y + (size.cy / 2)
	};

	ctx->drawCircle(center.x, center.y, (size.cx / 2), false);

	if (this->isChosen())
		ctx->drawCircle(center.x, center.y, (size.cx / 4), true);
}