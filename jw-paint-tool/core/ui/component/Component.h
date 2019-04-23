#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

#include "EasyGraphics.h"
#include "core\enum\LayoutManagerEnum.h"
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
		// Returns the difference between the (left and right) and
		// (top and bottom) of the Component's rect in SIZE form.
		//
		inline SIZE getSize() const;

		//
		// Returns the states of the component
		//
		inline std::vector<ComponentState> getStates() const;

		//
		// Returns a pointer to the parent of the Component
		//
		inline Component *getParent() const;

		//
		// Returns a pointer to the effective StyleSet.
		//
		// See core\ui\style\ComponentStyle.h for more.
		//
		inline const ComponentStyle::StyleSet *getStyleSet() const;

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
		inline void setTextColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setBgColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setLineColour(const int &colour, ComponentState state = COMPONENT_STATE_NORMAL);
		inline void setLineThickness(const int &thickness, ComponentState state = COMPONENT_STATE_NORMAL);

		//
		// Sets the hidden property
		//
		inline void setHidden(const bool &_hidden);

		//
		// Sets the function used to determine whether or not the Component is
		// drawn
		//
		inline void showIf(std::function<bool()> _fn_show_if);

		//
		// Returns true when both hidden is false and fn_show_if returns true
		//
		inline bool isHidden() const;

		//
		// Returns false; the base Component is not interactive
		//
		inline virtual bool isInteractive() const;

		//
		// Returns false; the base Component is not a grouping of components
		//
		inline virtual bool isComponentGroup() const;

		//
		// Returns true when the given state is within the Component's states
		// vector
		//
		inline bool hasState(ComponentState state) const;

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
			const	std::string	&id
		);

		Component(
			const	std::string	&id,
			const	SIZE		&size
		);

		//
		// Returns the pointer to the style property
		//
		inline const ComponentStyle *getStyle() const;

		//
		// Gives the Component a new width, height, and position
		//
		inline void setRect(const RECT &_rect);

		//
		// Gives the Component a new origin.
		//
		// If reposition is true, then the Component's position will be
		// adjusted such that the physical location of the origin does
		// not appear to have moved.
		//
		inline void setOrigin(const POINT &_origin, const bool &reposition = false);

		//
		// Gives the Component a new width and height
		//
		void setSize(SIZE size);

		//
		// Adds the state to the Component's states vector
		//
		void setState(ComponentState state);

		//
		// Removes the state from the Component's states vector
		//
		void unsetState(ComponentState state);

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
		// The states the Component has
		//
		std::vector<ComponentState> states;

		//
		// The style of the Component
		//
		ComponentStyle *style;

		//
		// Determines how the Component will be aligned within its parent rect
		//
		AlignStrategy alignment;

		//
		// When true, the Component is not drawn and cannot be interacted with.
		//
		// A Component is drawn when hidden is false, and fn_show_if returns
		// true.
		//
		bool hidden;

		//
		// When this function returns true, the Component will be drawn
		// (assuming hidden is also false).
		//
		// Much like hidden, if this function returns false, the Component will
		// not be interactive.
		//
		// A Component is drawn when fn_show_if returns true, and hidden is
		// false.
		//
		// By default, this function returns true.
		//
		std::function<bool()> fn_show_if;
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

std::vector<paint_tool::ComponentState> paint_tool::Component::getStates() const {
	return states;
}

paint_tool::Component *paint_tool::Component::getParent() const {
	return parent;
}

const paint_tool::ComponentStyle::StyleSet *paint_tool::Component::getStyleSet() const {
	return style->getEffectiveStyleSet(states);
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

const paint_tool::ComponentStyle *paint_tool::Component::getStyle() const {
	return style;
}

void paint_tool::Component::setRect(const RECT &_rect) {
	rect = _rect;
}

void paint_tool::Component::setOrigin(const POINT &_origin, const bool &reposition) {

	if (reposition) {

		POINT new_position = getPosition();

		/* get the position of the point where the origin lies */

		new_position.x += origin.x;
		new_position.y += origin.y;

		/* adjust the position to make it appear that the physical location
	       of the origin hasn't moved */

		new_position.x -= _origin.x;
		new_position.y -= _origin.y;

		setPosition(new_position);
	}

	origin = _origin;
}

void paint_tool::Component::setParent(Component *_parent) {
	parent = _parent;
}

void paint_tool::Component::setAlignment(AlignStrategy _alignment) {
	alignment = _alignment;
}

void paint_tool::Component::setTextColour(const int &colour, ComponentState state) {
	style->setTextColour(colour, state);
}

void paint_tool::Component::setBgColour(const int &colour, ComponentState state) {
	style->setBgColour(colour, state);
}

void paint_tool::Component::setLineColour(const int &colour, ComponentState state) {
	style->setLineColour(colour, state);
}

void paint_tool::Component::setLineThickness(const int &thickness, ComponentState state) {
	style->setLineThickness(thickness, state);
}

void paint_tool::Component::setHidden(const bool &_hidden) {
	hidden = _hidden;
}

void paint_tool::Component::showIf(std::function<bool()> _fn_show_if) {
	fn_show_if = _fn_show_if;
}

bool paint_tool::Component::isHidden() const {
	return (!hidden && fn_show_if());
}

bool paint_tool::Component::isInteractive() const {
	return false;
}

bool paint_tool::Component::isComponentGroup() const {
	return false;
}

bool paint_tool::Component::hasState(ComponentState state) const {
	return (std::find(states.begin(), states.end(), state) != states.end());
}

void paint_tool::Component::recalculateSize() {
	//
}