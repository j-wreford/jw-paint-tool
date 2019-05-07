#pragma once

#include "core\Singleton.h"
#include "src\component\PolygonDrawing.h"
#include "src\component\LineDrawing.h"

namespace paint_tool {

	class DrawingFactory :
		public Singleton<DrawingFactory> {
	public:

		friend class Singleton<DrawingFactory>;
		
		//
		// Instantiates the correct concrete Drawing class and returns as a
		// generic p_component_t, so that it may be added to the Canvas
		//
		p_component_t makeDrawing(
			const	std::string					&type,
			const	POINT						&pos,
			const	ComponentStyle::StyleSet	&style_set,
			const	std::list<POINT *>			&points
		);

	private:

		DrawingFactory();
		~DrawingFactory();

		//
		// A counter that tracks the number of Drawings that have been created
		//
		int count;
	};
}