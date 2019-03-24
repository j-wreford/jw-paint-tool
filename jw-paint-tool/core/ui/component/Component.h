#pragma once

#include <string>
#include <memory>
#include <algorithm>

#include "EasyGraphics.h"
#include "core\ui\layout\LayoutManagerEnum.h"
#include "core\enum\ComponentStateEnum.h"
#include "core\ui\style\ComponentStyle.h"

//
// Component
//
// A pure virtual class for all user interface components to inherit from.
//

namespace paint_tool {

	class Component {
	public:

		virtual ~Component();

		//
		// Draws the component to the given EasyGraphics context
		//
		virtual void drawComponent(EasyGraphics *ctx) const = 0;

		//
		// Returns the type of the Component given as a string.
		//
		// For example, a StaticLabel would return static_label.
		//
		virtual std::string getComponentType() const = 0;

		//
		// Returns the string used to identify the Component
		//
		inline std::string getId() const;

		//
		// Returns the rectangle that represents the Component's position
		// and size.
		//
		// The absolute variant will modify the return rect so that its position
		// is relative to the upper-left pixel of the whole window.
		//
		inline RECT getRect() const;
		RECT getAbsoluteRect() const;

		//
		// Returns the point where (0,0) is within the Component's rect
		//
		inline POINT getOrigin() const;

		//
		// Returns the top and left values of the Component's rect in POINT
		// form, relative to its parent.
		//
		// The absolute variant will return its position relative to the
		// upper-left pixel of the whole window.
		//
		inline POINT getPosition() const;
		POINT getAbsolutePosition() const;

		//
		// Returns the difference between the (width and height) and
		// (top and bottom) of the Component's rect in SIZE form.
		//
		inline SIZE getSize() const;

		//
		// Returns a pointer to the parent of the Component
		//
		inline Component *getParent() const;

		//
		// Returns a pointer to the appropriate style set.
		//
		// This version will always return the normal state.
		//
		inline virtual const ComponentStyle::StyleSet *getStyleSet() const;

		//
		// Returns the alignment of the Component
		//
		inline AlignStrategy getAlignment() const;

		//
		// Gives the Component a new position
		//
		void setPosition(POINT position);

		//
		// Positions the Component within the parent boundaries
		//
		inline void positionLeft();
		void positionRight();
		void positionCenter();
		inline void positionTop();
		void positionBottom();
		void positionMiddle();

		//
		// Sets the pointer to the parent Component
		//
		inline void setParent(Component *_parent);

		//
		// Sets the alignment of the Component
		//
		inline void setAlignment(AlignStrategy _alignment);

		//
		// Sets the corresponding style property for the given component state.
		//
		// If state is not given, then the default style set is updated.
		//
		inline void setTextColour(COLORREF *text_colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setBgColour(COLORREF *bg_colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setLineColour(COLORREF *line_colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setLineThickness(int line_thickness, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setStyleSet(ComponentStyle::StyleSet *style_set, ComponentState state = COMPONENT_STATE_NORMAL);

		//
		// Returns false; the base Component is not interactive
		//
		inline virtual bool isInteractive() const;

		//
		// Returns false; the base Component is not a grouping of components
		//
		inline virtual bool isComponentGroup() const;

		//
		// Instructs the Component to recalculate its size.
		//
		// This virtual method is useful for scenarios where the the phsyical
		// size have changed, but the logical representation has not.
		//
		// For example, when a StaticLabel has its text changed, there is a
		// disparity between its rectangle size and the physical pixel
		// measurement of its size.
		//
		inline virtual void recalculateSize();

	protected:

		Component(
			const	std::string	&id,
			const	std::string &style_set_id = "default"
		);

		Component(
			const	std::string	&id,
			const	SIZE		&size,
			const	std::string &style_set_id = "default"
		);

		//
		// Gives the Component a new width, height, and position
		//
		inline void setRect(const RECT &_rect);

		//
		// Gives the Component a new origin
		//
		inline void setOrigin(const POINT &_origin);

		//
		// Gives the Component a new width and height
		//
		void setSize(SIZE size);

		//
		// Sets the corresponding uses_ flag to true.
		//
		// Called by a concrete Component class whos draw method uses the
		// corresponding property in some way.
		//
		// For example, a concrete Component who draws text will want to call
		// willuseFrontColour() in their constructor.
		//
		inline void willUsePen(), willUseBackColour(), willUseFrontColour();

	private:

		//
		// The string used to uniquely identify the Component 
		//
		std::string id;

		//
		// The combined position and size of the Component, not taking into
		// account the origin offset
		//
		RECT rect;

		//
		// The point within the rect of which (0,0) lies at
		//
		POINT origin;

		//
		// A pointer to the parent of the Component.
		//
		// This will be a nullptr unless the Component has been added to a
		// ComponentGroup.
		//
		Component *parent;

		//
		// The style of the Component
		//
		ComponentStyle *style;

		//
		// Determines how the Component will be aligned within its parent rect
		//
		AlignStrategy alignment;

		//
		// Set to true when the Component intends to use a drawing method
		// which uses the corresponding property
		//
		bool uses_bg, uses_fg, uses_pen;
	};

	typedef std::unique_ptr<Component> p_component_t;
}

std::string paint_tool::Component::getId() const {
	return id;
}

RECT paint_tool::Component::getRect() const {
	return rect;
}

POINT paint_tool::Component::getOrigin() const {
	return origin;
}

POINT paint_tool::Component::getPosition() const {

	return POINT{
		rect.left,
		rect.top
	};
}

SIZE paint_tool::Component::getSize() const {

	return SIZE{
		rect.right - rect.left,
		rect.bottom - rect.top
	};
}

paint_tool::Component *paint_tool::Component::getParent() const {
	return parent;
}

const paint_tool::ComponentStyle::StyleSet *paint_tool::Component::getStyleSet() const {
	return style->getStyleSet(COMPONENT_STATE_NORMAL);
}

paint_tool::AlignStrategy paint_tool::Component::getAlignment() const {
	return alignment;
}

void paint_tool::Component::positionLeft() {

	setPosition(POINT{
		0,
		getPosition().y
	});
}

void paint_tool::Component::positionTop() {

	setPosition(POINT{
		getPosition().x,
		0
	});
}

void paint_tool::Component::setRect(const RECT &_rect) {
	rect = _rect;
}

void paint_tool::Component::setOrigin(const POINT &_origin) {
	origin = _origin;
}

void paint_tool::Component::setParent(Component *_parent) {
	parent = _parent;
}

void paint_tool::Component::setAlignment(AlignStrategy _alignment) {
	alignment = _alignment;
}

void paint_tool::Component::setTextColour(COLORREF *colour, ComponentState state) {
	style->getStyleSet(state)->text_colour = colour;
}

void paint_tool::Component::setBgColour(COLORREF *colour, ComponentState state) {
	style->getStyleSet(state)->bg_colour = colour;
}

void paint_tool::Component::setLineColour(COLORREF *colour, ComponentState state) {
	style->getStyleSet(state)->line_colour = colour;
}

void paint_tool::Component::setLineThickness(int line_thickness, ComponentState state) {
	style->getStyleSet(state)->line_thickness = new int(line_thickness);
}

void paint_tool::Component::setStyleSet(ComponentStyle::StyleSet *style_set, ComponentState state) {
	style->setStyleSet(style_set, state);
}

bool paint_tool::Component::isInteractive() const {
	return false;
}

bool paint_tool::Component::isComponentGroup() const {
	return false;
}

void paint_tool::Component::recalculateSize() {
	//
}

void paint_tool::Component::willUsePen() {
	uses_pen = true;
}

void paint_tool::Component::willUseFrontColour() {
	uses_fg = true;
}

void paint_tool::Component::willUseBackColour() {
	uses_bg = true;
}
