#pragma once

//
// IObserver
//
// Implements the observer aspect of the observer design pattern.
//
// The template argument, T, is the class type of the pointer given in the pure
// virtual update method.
//

namespace paint_tool {

	template <class T>
	class IObserver {
	public:

		//
		// Instructs the IObserver that the subject Observable has undergone a
		// state change, and this IObserver must update itself accordingly
		//
		virtual void update(T *subject) = 0;
	};
}
