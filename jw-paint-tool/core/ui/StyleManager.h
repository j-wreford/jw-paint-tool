#pragma once

#include <string>
#include <map>

#include "EasyGraphics.h"
#include "core\Singleton.h"

//
// StyleManager
//
// This singleton class aims to provide consistant styling across all Components
// within the application. Much like a css class, a Component is given a name to
// referencing a set of colours and pen settings held within the manager.
//
// Calling applyStyle() with the given 'class' will apply the changes to the
// given EasyGraphics context.
//

namespace paint_tool {

	class StyleManager :
		public Singleton<StyleManager> {
	public:

		friend class Singleton<StyleManager>;

		//
		// Struct for describing the style of a Component
		//
		struct ComponentStyle {
			int fg_colour = 0xffffff,
				bg_colour = 0x000000,
				line_colour = 0x000000,
				line_size = 1;
		};

		//
		// Adds a style set to the manager
		//
		void addStyleSet(
			const	std::string	&style_set_id,
			const	int			&fg_colour = 0xffffff,
			const	int			&bg_colour = 0x000000,
			const	int			&line_colour = 0x000000,
			const	int			&line_size = 1
		);

		//
		// Applys the style set with the given key to the given EasyGraphics
		//
		void applyStyleSet(const std::string &style_set_id, EasyGraphics *ctx);

	private:

		StyleManager();
		~StyleManager();

		//
		// A map of styles
		//
		std::map<std::string, ComponentStyle *> style_set_map;
	};
}