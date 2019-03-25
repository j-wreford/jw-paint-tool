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
		inline void setChosen(const bool &_chosen);

	private:

		//
		// True when the ChoiceComponent was the last one clicked inside its
		// containing ChoiceGroup
		//
		bool chosen;
	};
}

template <typename T>
paint_tool::ChoiceComponent<T>::ChoiceComponent(const std::string &id, T value) :
	ValueComponent<T>(id, value),
	chosen(false) {
	//
}

template <typename T>
paint_tool::ChoiceComponent<T>::~ChoiceComponent() {
	//
}

template <typename T>
bool paint_tool::ChoiceComponent<T>::isChosen() const {
	return chosen;
}

template <typename T>
void paint_tool::ChoiceComponent<T>::setChosen(const bool &_chosen) {
	chosen = _chosen;
}