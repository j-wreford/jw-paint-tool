#pragma once

#include <memory>
#include <map>
#include <functional>

#include "EasyGraphics.h"
#include "core\ui\component\ComponentGroup.h"
#include "core\ui\component\RootComponent.h"
#include "core\ui\component\StaticBox.h"
#include "core\ui\component\StaticLabel.h"
#include "core\ui\FontManager.h"
#include "core\ui\StyleManager.h"

//
// Window
//
// A class which can manage Components on top of EasyGraphics functions.
//

namespace paint_tool {

	class Window :
		public EasyGraphics {
	public:

		Window(
					HINSTANCE	hInstance,
			const	int			&width = 800,
			const	int			&height = 600
		);
		~Window();

		//
		// Draws each Component to the window
		//
		virtual void onDraw() override;

		//
		// Responds to key press events
		//
		virtual void onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override;

		//
		// Set flags
		//
		virtual void onChar(UINT nChar, UINT nRepCnt, UINT nFlags);

		//
		// Performs hit tests on Components, if they are interactive.
		//
		// Sets lmouse_down to true.
		//
		virtual void onLButtonDown(UINT nFlags, int x, int y) override;

		//
		// Sets lmouse_down to false
		//
		virtual void onLButtonUp(UINT nFlags, int x, int y) override;

		//
		// Moves the focused Component, if it is draggable
		//
		virtual void onMouseMove(UINT nFlags, int x, int y) override;

	protected:

		//
		// Adds a component to the components collection
		//
		void addComponent(p_component_t &component);

	private:

		//
		// The root component of which all Components are added to
		//
		p_root_component_t root_component;

		//
		// True when the left mouse mouse button has been pressed,
		// but not released
		//
		bool lmouse_down;

		//
		// When true, the id of a component is drawn above its position
		//
		bool debug_show_ids;

		//
		// When true, all components are drawn with a surrounding border
		//
		bool debug_show_borders;

		//
		// When true, lines between the each Component boundary and its
		// container are drawn
		//
		bool debug_show_position_lines;

		//
		// Draws a single Component
		//
		void drawSingleComponent(const Component *component);

		//
		// Writes the id of the given Component above its position
		//
		void drawDebugComponentId(const Component *component);

		//
		// Frames the given Component's rect
		//
		void drawDebugComponentBorder(const Component *component);

		//
		// Draws lines fomr the Component border to the boundary of its parent.
		//
		// If the given component does not have a parent, then the lines are
		// drawn to the screen boundaries.
		//
		void drawDebugComponentPositionLines(const Component *component);

		//
		// Walks the Component tree and executes the given function each time
		// it visits a branch or leaf
		//
		static void componentWalker(
			Component *component,
			std::function<void(Component *component)> fn
		);
	};
}