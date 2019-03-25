#pragma once

#include "core\ui\component\ValueComponent.h"

namespace paint_tool {

	template <typename T>
	class ChoiceComponent :
		public ValueComponent<T> {
	public:

		ChoiceComponent(const std::string &id, T value);
		~ChoiceComponent();

		//
		// Returns the chosen property
		//
		inline bool isChosen() const;

		//
		// Sets the chosen property
		//
		inline void setChosen(const bool &chosen);
	};
}

template <typename T>
paint_tool::ChoiceComponent<T>::ChoiceComponent(const std::string &id, T value) :
	ValueComponent<T>(id, value) {
	//
}

template <typename T>
paint_tool::ChoiceComponent<T>::~ChoiceComponent() {
	//
}

template <typename T>
bool paint_tool::ChoiceComponent<T>::isChosen() const {
	return this->hasState(COMPONENT_STATE_CHOSEN);
}

template <typename T>
void paint_tool::ChoiceComponent<T>::setChosen(const bool &chosen) {
	if (chosen)
		this->setState(COMPONENT_STATE_CHOSEN);
	else
		this->unsetState(COMPONENT_STATE_CHOSEN);
}