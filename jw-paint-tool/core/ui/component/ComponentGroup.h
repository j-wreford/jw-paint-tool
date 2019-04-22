#pragma once

#include <list>
#include <algorithm>

#include "core\ui\component\InteractiveComponent.h"
#include "core\ui\component\FixedSpace.h"

//
// ComponentGroup
//
// Collects a group of Components into one single Component.
//
// The collection is stored as a List. Originally, this project had used an
// associative container but this was changed when the order of which Components
// were addded became important.
//

namespace paint_tool {

	//
	// The string used to represent the Component
	//
	const std::string CPMNT_GROUP = "component_group";

	class ComponentGroup :
		public InteractiveComponent {
	public:

		ComponentGroup(
			const	std::string	&id,
			const	bool		&fill_background = false
		);
		virtual ~ComponentGroup();

		//
		// Draws the background, if required, of the ComponentGroup.
		//
		// This method does not need to call the drawComponent() method of its
		// children, as the Window drawSingleComponent() method does this.
		//
		virtual void drawComponent(EasyGraphics *ctx) const override;

		//
		// Updates the active_component property and calls onLeftMosueDownHit
		// to the first child Component whose hit test passes
		//
		virtual void onLeftMouseDownHit(const POINT &mouse) override;
		virtual void onLeftMouseDownLostHit() override;

		//
		// Updates the focused_component property and calls onLeftMouseUpHit
		// to the first child Component whose hit test passes
		//
		virtual void onLeftMouseUpHit(const POINT &mouse) override;
		virtual void onLeftMouseUpLostHit() override;

		//
		// Updates the hovered_component property and calls onLeftMouseUpHit
		// to the first child Component whose hit test passes
		//
		virtual void onMouseMoveHit(const POINT &mouse, const bool& lmouse_down) override;
		virtual void onMouseMoveLostHit() override;

		//
		// Returns CPMNT_GROUP
		//
		inline virtual std::string getComponentType() const override;

		//
		// Returns the strategy used to lay out child components
		//
		inline LayoutStrategy getLayoutStrategy() const;

		//
		// Returns true; this is a grouping of Components
		//
		inline virtual bool isComponentGroup() const;

		//
		// Returns true when at least one Component held within the group is interactive,
		// or when draggable is set to true for the ComponentGroup
		//
		virtual bool isInteractive() const override;

		//
		// Returns the collection containing the child Components
		//
		inline const std::list<p_component_t> *getChildComponents() const;
		inline std::list<p_component_t> *getChildComponents();

		//
		// Returns the minimum size of the ComponentGroup
		//
		inline SIZE getMinimumSize() const;

		//
		// Adds a Component to the ComponentGroup
		//
		void addComponent(p_component_t &component);

		//
		// Adds a Spacer component to the group
		//
		void addVerticalSpace(const int& height);
		void addHorizontalSpace(const int& width);

		//
		// Sets the strategy to be used by the LayoutManager to position
		// child components
		//
		inline void setLayoutStrategy(LayoutStrategy _layout);

		//
		// Sets the minimum size of the ComponentGroup
		//
		inline void setMinimumSize(const SIZE &_minimum_size);

		//
		// Recalculates the union rectangle between all child Component rects
		//
		virtual void recalculateSize() override;

	protected:

		//
		// Returns the Component with the given id
		//
		inline Component *getComponent(const std::string &id);

		//
		// Returns the focused component
		//
		inline InteractiveComponent *getFocusedComponent();

		//
		// Returns the active component
		//
		inline InteractiveComponent *getActiveComponent();

		//
		// Returns the hovered component
		//
		inline InteractiveComponent *getHoveredComponent();

		//
		// Sets the fill_background property
		//
		inline void setFillBackground(const bool &_fill_background);

	private:

		//
		// Determines how to lay out the components contained
		// within the group
		//
		LayoutStrategy layout;

		//
		// A list of child ui Components
		//
		std::list<paint_tool::p_component_t> components;

		//
		// The child InteractiveComponent who last responded to
		// left mouse down hit
		//
		InteractiveComponent *last_lmdh;

		//
		// The child InteractiveComponent who last responded to
		// left mouse up hit
		//
		InteractiveComponent *last_lmuh;

		//
		// The child InteractiveComponent who last responded to
		// mouse move hit
		//
		InteractiveComponent *last_mmh;

		//
		// Defines the minimum size of the ComponentGroup
		//
		SIZE minimum_size;

		//
		// When true, the ComponentGroup will fill its background with bg_colour
		//
		bool fill_background;

		//
		// Returns a pointer to the first interactive child component whose
		// hit test passes
		//
		InteractiveComponent *getFirstHitInteractiveComponent(const POINT &mouse);
	};

	typedef std::unique_ptr<ComponentGroup> p_component_group_t;
}

std::string paint_tool::ComponentGroup::getComponentType() const {
	return CPMNT_GROUP;
}

paint_tool::LayoutStrategy paint_tool::ComponentGroup::getLayoutStrategy() const {
	return layout;
}

bool paint_tool::ComponentGroup::isComponentGroup() const {
	return true;
}

const std::list<paint_tool::p_component_t> *paint_tool::ComponentGroup::getChildComponents() const {
	return &components;
}

std::list<paint_tool::p_component_t> *paint_tool::ComponentGroup::getChildComponents() {
	return &components;
}

SIZE paint_tool::ComponentGroup::getMinimumSize() const {
	return minimum_size;
}

void paint_tool::ComponentGroup::setLayoutStrategy(LayoutStrategy _layout) {
	layout = _layout;
}

void paint_tool::ComponentGroup::setMinimumSize(const SIZE &_minimum_size) {
	minimum_size = _minimum_size;
	recalculateSize();
}

paint_tool::InteractiveComponent *paint_tool::ComponentGroup::getFocusedComponent() {
	return last_lmuh;
}

paint_tool::InteractiveComponent *paint_tool::ComponentGroup::getActiveComponent() {
	return last_lmdh;
}

paint_tool::InteractiveComponent *paint_tool::ComponentGroup::getHoveredComponent() {
	return last_mmh;
}

paint_tool::Component *paint_tool::ComponentGroup::getComponent(const std::string &id) {

	Component *component = nullptr;

	auto it = std::find_if(components.begin(), components.end(), [&id](p_component_t &component) {
		return (component->getId() == id);
	});

	if (it != components.end())
		component = it->get();

	return component;
}

void paint_tool::ComponentGroup::setFillBackground(const bool &_fill_background) {
	fill_background = _fill_background;
}