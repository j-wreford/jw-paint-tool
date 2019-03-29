#pragma once

#include <vector>

#include "core\IObserver.h"

//
// Observable
//
// Implements the subject aspect of the observer design pattern.
//
// It is the responsibility of the derived class to call notifyObservers
// whenever its own state changes.
//

namespace paint_tool {

	class Observable {
	public:

		//
		// Registers an IObserver that shall be notified whenever
		// the state of this Observable changes
		//
		inline void registersObserver(IObserver *observer);

	protected:

		inline Observable();
		inline ~Observable();

		//
		// Calls update on each registered IObserver
		//
		inline void notifyObservers();

	private:

		//
		// A container of all registers IObservers that'll be notified whenever
		// the state of Observable changes
		//
		std::vector<IObserver *> observers;
	};
}

paint_tool::Observable::Observable() {
	//
}

paint_tool::Observable::~Observable() {
	//
}

void paint_tool::Observable::registersObserver(IObserver *observer) {
	observers.push_back(observer);
}

void paint_tool::Observable::notifyObservers() {

	for (IObserver *observer : observers)
		observer->update();
}