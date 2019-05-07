#pragma once

#include "core\ui\component\ComponentGroup.h"
#include "core\Observable.h"

//
// ValueComponent<T>
//
// A Component who owns a value that can be retreived by calling getValue.
//
// This would be the base class for choice components, text fields, etc, to
// inherit from.
//
// ValueComponent is Observable. Other IObserver objects can listen to this
// component and update itself whenever the value changes.
//

namespace paint_tool {

	template <typename T>
	class ValueComponent :
		public ComponentGroup,
		public Observable<ValueComponent<T>> {
	public:

		ValueComponent(const std::string &id, T value);
		~ValueComponent();

		//
		// Force the ValueComponent to be interactive, even if it has no child
		// components who are considered interactive
		//
		inline bool isInteractive() const;

		//
		// Returns the value the ValueComponent holds
		//
		inline T getValue() const;

		//
		// Sets the value the ValueComponent holds.
		//
		// This method is virtual so that further derived ValueComponents
		// may hook into the setValue chain. For instance, when a ChoiceGroup
		// has its value changed, it must also notify the correct child
		// ChoiceComponent that it was chosen.
		//
		virtual inline void setValue(T _value);

	private:

		//
		// The value the ValueComponent holds
		//
		T value;
	};
}

template <typename T>
paint_tool::ValueComponent<T>::ValueComponent(const std::string &id, T value) :
	ComponentGroup(id),
	value(value) {
	//
}

template <typename T>
paint_tool::ValueComponent<T>::~ValueComponent() {
	//
}

template <typename T>
bool paint_tool::ValueComponent<T>::isInteractive() const {
	return true;
}

template <typename T>
T paint_tool::ValueComponent<T>::getValue() const {
	return value;
}

template <typename T>
void paint_tool::ValueComponent<T>::setValue(T _value) {
	value = _value;
	this->notifyObservers();
}