#pragma once

#include "core\ui\component\ComponentGroup.h"
#include "core\ui\component\ChoiceComponent.h"

//
// ChoiceGroup
//
// This Component is a ComponentGroup who can return the value of the last
// clicked ChoiceComponent that has been added to it.
// If no such components exist in the group, or if one hasn't been clicked yet,
// then default_value is returned.
//

namespace paint_tool {

	template <typename T>
	class ChoiceGroup :
		public ComponentGroup {
	public:

		ChoiceGroup(const std::string &id, T default_value);
		~ChoiceGroup();

		//
		// Sets chosen_component to the group's focused component, if it is a
		// ChoiceComponent
		//
		virtual void onLeftMouseUpHit(const POINT& mouse) override;

		//
		// Returns the value of chosen_component, or default_value if
		// chosen_component is a nullptr
		//
		T getChosenValue() const;

	private:

		//
		// The value returned when chosen_component is a nullptr
		//
		T default_value;

		//
		// The currently chosen ChoiceComponent
		//
		ChoiceComponent<T> *chosen_component;
	};
}

template <typename T>
void paint_tool::ChoiceGroup<T>::onLeftMouseUpHit(const POINT& mouse) {

	ChoiceComponent<T> *choice =
		dynamic_cast<ChoiceComponent<T> *>(getFocusedComponent());

	if (choice) {

		if (chosen_component)
			chosen_component->setChosen(false);

		choice->setChosen(true);

		chosen_component = choice;
	}
}

template <typename T>
T paint_tool::ChoiceGroup<T>::getChosenValue() const {
	
	T value = default_value;

	if (chosen_component)
		value = chosen_component->getValue();

	return value;
}

template <typename T>
paint_tool::ChoiceGroup<T>::ChoiceGroup(const std::string &id, T default_value) :
	ComponentGroup(id),
	default_value(default_value) {
	//
}

template <typename T>
paint_tool::ChoiceGroup<T>::~ChoiceGroup() {
	//
}