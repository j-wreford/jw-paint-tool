#pragma once

#include "core\ui\component\ValueComponent.h"
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
		public ValueComponent<T> {
	public:

		ChoiceGroup(const std::string &id, T default_value);
		~ChoiceGroup();

		//
		// Sets chosen_component to the group's focused component, if it is a
		// ChoiceComponent
		//
		virtual void onLeftMouseUpHit(const POINT& mouse) override;

		//
		// In addition to updating the value, it correctly sets the chosen
		// child ChoiceComponent
		//
		virtual void setValue(T _value) override;

		//
		// Returns the value of chosen_component, or default_value if
		// chosen_component is a nullptr
		//
		inline T getChosenValue() const;

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
paint_tool::ChoiceGroup<T>::ChoiceGroup(const std::string &id, T default_value) :
	ValueComponent<T>(id, default_value),
	default_value(default_value),
	chosen_component(nullptr) {
	//
}

template <typename T>
paint_tool::ChoiceGroup<T>::~ChoiceGroup() {
	//
}

template <typename T>
void paint_tool::ChoiceGroup<T>::onLeftMouseUpHit(const POINT& mouse) {

	ValueComponent<T>::onLeftMouseUpHit(mouse);

	ChoiceComponent<T> *choice =
		dynamic_cast<ChoiceComponent<T> *>(this->getFocusedComponent());

	if (choice) {

		if (chosen_component)
			chosen_component->setChosen(false);

		choice->setChosen(true);
		this->setValue(choice->getValue());

		chosen_component = choice;
	}
}

template <typename T>
void paint_tool::ChoiceGroup<T>::setValue(T _value) {

	ValueComponent<T>::setValue(_value);

	/* find the child ChoiceComponent that has this value */

	ComponentGroup *group = dynamic_cast<ComponentGroup *>(this);

	auto components = group->getChildComponents();

	auto it = std::find_if(components->begin(), components->end(), [&_value](p_component_t &component) {
		
		if (ValueComponent<T> *tmp = dynamic_cast<ValueComponent<T> *>(component.get()))
			return tmp->getValue() == _value;
		return false;
	});

	/* if found, notify the choice component that it is chosen */

	if (it != components->end()) {

		if (chosen_component)
			chosen_component->setChosen(false);

		ChoiceComponent<T> *choice = dynamic_cast<ChoiceComponent<T> *>(it->get());
		choice->setChosen(true);

		chosen_component = choice;
	}
}

template <typename T>
T paint_tool::ChoiceGroup<T>::getChosenValue() const {
	//return chosen_component ? chosen_component->getValue() : default_value;
	return this->getValue();
}