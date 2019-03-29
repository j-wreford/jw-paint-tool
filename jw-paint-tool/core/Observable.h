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
		void registersObserver(IObserver *observer);

	protected:

		Observable();
		~Observable();

		//
		// Calls update on each registered IObserver
		//
		void notifyObservers();

	private:

		//
		// A container of all registers IObservers that'll be notified whenever
		// the state of Observable changes
		//
		std::vector<IObserver *> observers;
	};
}
