#pragma once

#include "core\Singleton.h"
#include "core\Observable.h"
#include "core\IObserver.h"
#include "core\ui\component\ValueComponent.h"
#include "src\enum\ToolChoiceEnum.h"
#include "src\component\Drawing.h"

//
// AppData
//
// The data model used by the application to store global states that various
// areas of the program can access and use.
//

namespace paint_tool {

	class AppData :
		public Singleton<AppData>,
		public Observable<AppData>,
		public IObserver<ValueComponent<ToolChoice>> {
	public:

		friend class Singleton<AppData>;

		//
		// Application constants
		//
		static const COLORREF UI_PANEL_BG;
		static const COLORREF UI_PANEL_TEXT;
		static const COLORREF UI_PANEL_HEADING;
		static const COLORREF UI_PANEL_SUB_HEADING;
		static const COLORREF UI_PANEL_ACTIVE;
		static const COLORREF UI_PANEL_FOCUS;
		static const COLORREF UI_PANEL_HOVER;

		//
		// Updates the tool_choice property whenever the subject Observable
		// undergoes a state change
		//
		inline virtual void update(ValueComponent<ToolChoice> *observable) override;

		//
		// Returns the tool_choice property
		//
		inline ToolChoice getToolChoice() const;

		//
		// Returns the drawing_choice property
		//
		inline Drawing *getDrawingChoice() const;

		//
		// Sets the drawing_choice property
		//
		inline void setDrawingChoice(Drawing *drawing);

	private:

		AppData();
		~AppData();

		//
		// The currently selected tool the user has chosen
		//
		ToolChoice tool_choice;

		//
		// The currently selected drawing
		//
		Drawing *drawing_choice;
	};
}

void paint_tool::AppData::update(ValueComponent<ToolChoice> *observable) {
	tool_choice = observable->getValue();
}

paint_tool::ToolChoice paint_tool::AppData::getToolChoice() const {
	return tool_choice;
}

paint_tool::Drawing *paint_tool::AppData::getDrawingChoice() const {
	return drawing_choice;
}

void paint_tool::AppData::setDrawingChoice(Drawing *drawing) {
	drawing_choice = drawing;
	notifyObservers();
}