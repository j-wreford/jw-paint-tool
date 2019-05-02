#pragma once

#include "core\IObserver.h"
#include "core\ui\component\ChoiceGroup.h"
#include "core\ui\component\StaticLabel.h"
#include "core\ui\component\TextField.h"
#include "src\AppData.h"
#include "src\component\Drawing.h"
#include "src\component\ColourChoiceGroup.h"

//
// UISelectedDrawing
//
// A pre-packaged ComponentGroup which offers controls to edit properties of
// a selected Drawing.
//
// This class observes AppData, so that it may update labels and controls
// whenever AppData is updated.
//

namespace paint_tool {

	class UISelectedDrawing :
		public ComponentGroup,
		public IObserver<AppData>,
		public IObserver<ValueComponent<std::wstring>>,
		public IObserver<ValueComponent<int>> {
	public:

		UISelectedDrawing();
		~UISelectedDrawing();

		//
		// Updates the labels and available controls, depending on the currently
		// selected drawing
		//
		virtual void update(AppData *subject) override;

		//
		// Updates selected component properties based on the id of the given
		// subject string ValueComponent
		//
		virtual void update(ValueComponent<std::wstring> *subject) override;

		//
		// Updates selected component properties based on the id of the given
		// subject integer ValueComponent
		//
		virtual void update(ValueComponent<int> *subject) override;

	private:

		//
		// Creates and formats a TextField to be used in this group
		//
		p_component_t makeTextField(
			const	std::string		&id,
			const	SIZE			&size,
			const	std::wstring	&placeholder
		);
	};
}