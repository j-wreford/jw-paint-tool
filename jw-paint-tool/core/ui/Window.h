#pragma once

#include <memory>
#include <map>
#include <functional>

#include "EasyGraphics.h"
#include "core\ui\component\ComponentGroup.h"
#include "core\ui\component\RadioGroup.h"
#include "core\ui\component\StaticBox.h"
#include "core\ui\component\StaticLabel.h"
#include "core\ui\component\StaticImage.h"
#include "core\ui\component\Button.h"
#include "core\ui\layout\LayoutManager.h"
#include "core\ui\FontManager.h"

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
		// Returns the RootComponent
		//
		ComponentGroup *getRootComponent();

		//
		// Adds a component to the components collection
		//
		void addComponent(p_component_t &component);

	private:

		//
		// The root component of which all Components are added to
		//
		p_component_group_t root_component;

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
		// When true, the position of a component is drawn below its position
		//
		bool debug_show_pos;

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
		// Draws the given Component and draws child Components recursively.
		//
		// The current_ parameters are the colours currently being used. After
		// a child Component is drawn using this method, the colours are set
		// back to the current_ ones.
		//
		// This allows Components to inherit the colours of a parent if one
		// isn't specified.
		//
		void componentDrawer(
			const Component *component,
			int	current_text_col,
			int	current_bg_col,
			int	current_line_col,
			int	current_line_thickness
		);

		//
		// Writes the id of the given Component above its position
		//
		void drawDebugComponentId(const Component *component);

		//
		// Writes the position of the given Component below its position
		//
		void drawDebugComponentPos(const Component *component);

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
	};
}