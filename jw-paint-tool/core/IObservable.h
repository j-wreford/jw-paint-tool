#pragma once

#include <vector>

#include "core\IObserver.h"

//
// Observable
//
// Implements the subject aspect of the observer design pattern.
//
// The notifyObservers method is a pure virtual method, left to be defined by
// concrete obserable classes. This is due to the fact that the state parameters
// that must be passed can differ, depending on the subject.
//
// It is the responsibility of the derived class to call notifyObservers
// whenever its own state changes.
//

namespace paint_tool {

	class IObservable {
	public:

		//
		// Registers an IObserver that shall be notified whenever
		// the state of this Observable changes
		//
		inline void registerObserver(IObserver *observer);

	protected:

		inline IObservable();
		inline ~IObservable();

		//
		// Calls update on each registered IObserver
		//
		inline virtual void notifyObservers() = 0;

	private:

		//
		// A container of all registers IObservers that'll be notified whenever
		// the state of Observable changes
		//
		std::vector<IObserver *> observers;
	};
}

paint_tool::IObservable::IObservable() {
	//
}

paint_tool::IObservable::~IObservable() {
	//
}

void paint_tool::IObservable::registerObserver(IObserver *observer) {
	observers.push_back(observer);
}