#pragma once

//
// IObserver
//
// Implements the observer aspect of the observer design pattern.
//
// The update method is a pure virtual method, left to be defined by concrete
// observer classes.
//

namespace paint_tool {

	class IObserver {
	public:

		//
		// Instructs the IObserver that the subject Observable has undergone a
		// state change, and this IObserver must update itself accordingly
		//
		virtual void update() = 0;
	};
}
