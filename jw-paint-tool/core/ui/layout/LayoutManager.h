#pragma once

#include "core\ui\component\Component.h"

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