#include "RootComponent.h"

paint_tool::RootComponent::RootComponent(
	const	std::string &style_set_id,
			HWND		h_window
) :
	ComponentGroup("root_component", POINT{0, 0}, style_set_id, true),
	h_window(h_window) {
	recalculateSize();
}

paint_tool::RootComponent::~RootComponent() {
	//
}

void paint_tool::RootComponent::recalculateSize() {

	RECT rect;
	::GetClientRect(h_window, &rect);

	setRect(rect);
}