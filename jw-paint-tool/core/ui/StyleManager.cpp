#include "StyleManager.h"

paint_tool::StyleManager::StyleManager() {
	addStyleSet("default");
}

paint_tool::StyleManager::~StyleManager() {

	for (auto& pair : style_set_map)
		delete pair.second;
}

void paint_tool::StyleManager::addStyleSet(
	const	std::string	&style_set_id,
	const	int			&fg_colour,
	const	int			&bg_colour,
	const	int			&line_colour,
	const	int			&line_size
) {

	ComponentStyle *style = new ComponentStyle{
		fg_colour, bg_colour, line_colour, line_size
	};

	style_set_map.insert(std::make_pair(
		style_set_id, style
	));
}

void paint_tool::StyleManager::applyStyleSet(
	const	std::string		&style_set_id,
			EasyGraphics	*ctx
) {

	auto search = style_set_map.find(style_set_id);

	if (search == style_set_map.end())
		search = style_set_map.find("default");

	ComponentStyle *style = search->second;

	ctx->selectBackColour(style->bg_colour);
	ctx->selectTextColour(style->fg_colour);
	ctx->setPenColour(style->line_colour, style->line_size);
}