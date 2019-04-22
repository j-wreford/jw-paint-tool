#pragma once

#include "core\Singleton.h"
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
		// The data model can observe ValueComponents which store a ToolChoice
		// value, in order to update the tool_choice property
		public IObserver<ValueComponent<ToolChoice>> {
	public:

		friend class Singleton<AppData>;

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

	private:

		inline AppData();
		inline ~AppData();

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

paint_tool::AppData::AppData() :
	tool_choice(TOOL_PEN_FREEHAND),
	drawing_choice(nullptr) {
	//
}

paint_tool::AppData::~AppData() {
	//
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