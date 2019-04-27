#pragma once

#include "core\IObserver.h"
#include "core\ui\component\ComponentGroup.h"
#include "core\ui\component\StaticLabel.h"
#include "core\ui\component\TextField.h"
#include "src\AppData.h"
#include "src\component\Drawing.h"

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
		public IObserver<AppData>{
	public:

		UISelectedDrawing();
		~UISelectedDrawing();

		//
		// Updates the labels and available controls, depending on the currently
		// selected drawing
		//
		virtual void update(AppData *subject) override;
	private:

		Drawing *selected_drawing;
	};
}