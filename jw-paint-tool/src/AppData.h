#pragma once

#include "core\Singleton.h"
#include "core\IObserver.h"
#include "core\ui\component\ChoiceGroup.h"
#include "src\enum\ToolChoiceEnum.h"

//
// AppData
//
// The data model used by the application to store global states that various
// areas of the program can access and use.
//

namespace paint_tool {

	class AppData :
		public Singleton<AppData>,
		// The data model can observe ChoiceGroups which store a ToolChoice
		// value, in order to update the tool_choice property
		public IObserver<ChoiceGroup<ToolChoice>> {
	public:

		friend class Singleton<AppData>;

		inline void update(ChoiceGroup<ToolChoice> *observable);

	private:

		AppData();
		~AppData();

		//
		// The currently selected tool the user has chosen
		//
		ToolChoice tool_choice;
	};
}

paint_tool::AppData::AppData() {
	//
}

paint_tool::AppData::~AppData() {
	//
}

void paint_tool::AppData::update(ChoiceGroup<ToolChoice> *observable) {
	tool_choice = observable->getChosenValue();
}