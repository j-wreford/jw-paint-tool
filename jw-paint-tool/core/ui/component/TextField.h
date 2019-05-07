#pragma once

#include "core\IObserver.h"
#include "core\ui\component\ValueComponent.h"
#include "core\ui\component\StaticBox.h"
#include "core\ui\component\StaticLabel.h"

//
// TextField
//
// A component which captures key strokes whenever it is active.
//

namespace paint_tool {

	class TextField :
		public ValueComponent<std::wstring>,
		public IObserver<ValueComponent<std::wstring>> {
	public:

		TextField(
			const	std::string		&id,
			const	SIZE			&size,
			const	std::wstring	&placeholder,
			const	std::string		&font_attr_set_id
		);
		~TextField();

		//
		// Deletes characters from the TextField
		//
		virtual void onKeyDown(UINT key, UINT flags) override;

		//
		// Updates the characters of the TextField
		//
		virtual void onChar(UINT key, UINT flags) override;

		//
		// Updates the real label text
		//
		virtual void update(ValueComponent<std::wstring> *subject) override;

		//
		// Returns true
		//
		inline virtual bool isInteractive() const override;

	private:

		//
		// The wstring displayed while the text field has no value
		//
		const std::wstring placeholder;
	};
}

bool paint_tool::TextField::isInteractive() const {
	return true;
}