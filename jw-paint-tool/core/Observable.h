#pragma once

#include <vector>

#include "core\IObserver.h"

//
// Observable
//
// Implements the subject aspect of the observer design pattern.
//
// The template argument, T, is the class type of the IObserver object that will
// observe this observable object.
//
// It is the responsibility of the concrete Observable class to call
// notifyObservers whenever its own state changes.
//

namespace paint_tool {

	template <class T>
	class Observable {
	public:

		//
		// Registers an IObserver that shall be notified whenever
		// the state of this Observable changes
		//
		inline void registerObserver(IObserver<T> *observer);

	protected:

		inline Observable();
		inline ~Observable();

		//
		// Calls update on each registered IObserver, passing each attached
		// IObserver object a pointer to this Observerable
		//
		inline void notifyObservers();

	private:

		//
		// A container of all registers IObservers that'll be notified whenever
		// the state of this Observable changes
		//
		std::vector<IObserver<T> *> observers;
	};
}

template <class T>
paint_tool::Observable<T>::Observable() {
	//
}

template <class T>
paint_tool::Observable<T>::~Observable() {
	//
}

template <class T>
void paint_tool::Observable<T>::registerObserver(IObserver<T> *observer) {
	observers.push_back(observer);
}

template <class T>
void paint_tool::Observable<T>::notifyObservers() {
	for (IObserver<T> *observer : observers)
		observer->update(static_cast<T *>(this));
}