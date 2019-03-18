#pragma once

#include <string>

#include "core\ui\component\Component.h"
#include "core\ui\FontManager.h"

//
// StaticLabel
//
// A simple component which will draw text to the screen.
//

namespace paint_tool {

	//
	// The string used to represent the Component
	//
	const std::string CPMNT_STATIC_LABEL = "static_label";

	class StaticLabel :
		public Component {
	public:

		StaticLabel(
			const	std::string		&id,
			const	POINT			&position,
			const	std::wstring	&text,
			const	std::string		&style_set_id = "default",
			const	std::string		&font_attr_set_id = "default"
		);
		~StaticLabel();

		//
		// Draws the label text to the given EasyGraphics context
		//
		virtual void drawComponent(EasyGraphics *ctx) const override;

		//
		// Returns CPMNT_STATIC_LABEL
		//
		inline virtual std::string getComponentType() const override;

		//
		// Returns the font resource handle 
		//
		inline std::string getFontAttributeSetId() const;

		//
		// Sets the font resource handle
		//
		inline void setFontAttributeSetId(const std::string &_font_attr_set_id);

		//
		// Sets the text of the Label
		//
		inline void setText(const std::wstring &_text);

		//
		// Recalculates the rect based on the width and height of drawn text,
		// taking into account the font handle used whilst drawing
		//
		virtual void recalculateSize() override;
			
	private:

		//
		// The font attribute set the Label will draw text with
		//
		std::string font_attr_set_id;

		//
		// The text the Label will display
		//
		std::wstring text;

		//
		// Returns the calculated width and height of the drawn text
		//
		SIZE calculateTextSize() const;
	};
}

std::string paint_tool::StaticLabel::getComponentType() const {
	return CPMNT_STATIC_LABEL;
}

std::string paint_tool::StaticLabel::getFontAttributeSetId() const {
	return font_attr_set_id;
}

void paint_tool::StaticLabel::setFontAttributeSetId(const std::string &_font_attr_set_id) {
	font_attr_set_id = _font_attr_set_id;
}

void paint_tool::StaticLabel::setText(const std::wstring &_text) {

	text = _text;

	/* make sure the label's rect is updated to reflect the new size of the text
	   given */

	setSize(calculateTextSize());
}