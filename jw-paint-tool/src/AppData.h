#pragma once

#include "core\Singleton.h"
#include "src\enum\ToolChoiceEnum.h"

namespace paint_tool {

	class AppData
		: public Singleton<AppData> {
	public:

		AppData();
		~AppData();

		//
		// Returns the currently selected tool
		//
		inline ToolChoice getToolChoice() const;

		//
		// Sets tool_choice
		//
		inline void setToolChoice(ToolChoice _tool_choice);

	private:

		//
		// The current tool that has been selected
		//
		ToolChoice tool_choice;
	};
}

paint_tool::ToolChoice paint_tool::AppData::getToolChoice() const {
	return tool_choice;
}

void paint_tool::AppData::setToolChoice(ToolChoice _tool_choice) {
	tool_choice = _tool_choice;
}