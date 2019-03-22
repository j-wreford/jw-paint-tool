#pragma once

#include "core\ui\layout\LayoutManagerEnum.h"
#include "core\ui\component\Component.h"
#include "core\ui\component\ComponentGroup.h"

//
// LayoutManager
//
// This class is responsible for positioning Components.
//
// Each ComponentGroup has a layout_style property. This property determines
// which strategy to use when the layout manager positions components.
// Only two strategies are available: LAYOUT_VERTICAL and LAYOUT_HORIZONTAL.
//
// The LayoutManager has no concept of wrapping to a new line.
//
// Each Component has a position_style property. This property determines how
// a Component is positioned on the oppose axis. For example, when using the
// LAYOUT_VERTICAL layout_style, the position_style property will determine
// its horizontal position (left, middle, or right).
//
// See LayoutManagerEnum.h for the enumerators which affect layouts.
//

namespace paint_tool {

	class LayoutManager {
	public:

		LayoutManager();
		~LayoutManager();

		//
		// Begins the layout process
		//
		void layout(Component *component, LayoutStrategy parent_layout = LAYOUT_MANUAL);

	private:

		//
		// Takes a ComponentGroup and lays out its Components vertically.
		//
		// This method will also call layout on each of its children.
		//
		void layoutVertically(ComponentGroup *group);

		//
		// Takes a ComponentGroup and lays out its Components horizontally.
		//
		// This method will also call layout on each of its children.
		//
		void layoutHorizontally(ComponentGroup *group);
	};
}

/*

in Window::onDraw()...
---
LayoutManager layout_manager = new LayoutManager(&root_component);
layout_manager->layout();



in LayoutManager::layout()...
---

if (component->isComponentGroup()) {

	LayoutStyle layout_style = component->getLayoutStyle();

	switch (layout_style) {

		case LAYOUT_MANUAL :
			// do nothing
		break;

		case LAYOUT_VERTICAL :

			layoutComponentsVertically();
			

		break;

		case LAYOUT_HORIZONTAL :

		break;
	}
}





*/