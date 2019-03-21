#pragma once

#include <map>
#include <algorithm>

#include "core\ui\component\InteractiveComponent.h"

//
// ComponentGroup
//
// Collects a group of Components into one single Component.
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
			const	POINT		&position,
			const	std::string &style_set_id = "default",
			const	bool		&fill_background = false
		);
		virtual ~ComponentGroup();

		//
		// Draws the background, if required, of the ComponentGroup.
		//
		// This method does not need to call the drawComponent() method of its
		// children, as the Window drawSingleComponent() method does this.
		//
		virtual void drawComponent(EasyGraphics *ctx) const;

		//
		// In addition to InteractiveComponent::onLeftMouseButtonDown,
		// this method will update the focused_component and active_component
		// properties.
		//
		// It will also call onLeftMouseButtonDown on each child component.
		//
		virtual void onLeftMouseButtonDown(const POINT &mouse) override;

		//
		// In addition to InteractiveComponent::onLeftMouseButtonUp,
		// this method will update the focused_component and active_component
		// properties.
		//
		// It will also call onLeftMouseButtonUp on each child component.
		//
		virtual void onLeftMouseButtonUp(const POINT &mouse) override;

		//
		// Calls InteractiveComponent::onMouseMove.
		//
		// It will also call onMouseMove on each child component.
		//
		virtual void onMouseMove(const POINT &mouse, const bool& lmouse_down) override;

		//
		// Returns CPMNT_GROUP
		//
		inline virtual std::string getComponentType() const override;

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
		inline const std::map<std::string, paint_tool::p_component_t> *getChildComponents() const;

		//
		// Adds a Component to the ComponentGroup
		//
		void addComponent(paint_tool::p_component_t &component);

		//
		// Recalculates the union rectangle between all child Component rects
		//
		virtual void recalculateSize() override;

	protected:

		//
		// TEMPORARY
		//
		inline InteractiveComponent *getFocusedComponent();

		//
		// Returns the Component with the given id
		//
		inline Component *getComponent(const std::string &id);

	private:

		//
		// A map of child ui Components
		//
		std::map<std::string, paint_tool::p_component_t> components;

		//
		// The last InteractiveComponent within the ComponentGroup to have its
		// hit test pass during the left mouse up event
		//
		InteractiveComponent *focused_component;

		//
		// The InteractiveComponent that was focused while the mouse is held
		// down
		//
		InteractiveComponent *active_component;

		//
		// When true, the ComponentGroup will fill its background with bg_colour
		//
		bool fill_background;
	};

	typedef std::unique_ptr<ComponentGroup> p_component_group_t;
}

std::string paint_tool::ComponentGroup::getComponentType() const {
	return CPMNT_GROUP;
}

bool paint_tool::ComponentGroup::isComponentGroup() const {
	return true;
}

const std::map<std::string, paint_tool::p_component_t> *paint_tool::ComponentGroup::getChildComponents() const {
	return &components;
}

paint_tool::InteractiveComponent *paint_tool::ComponentGroup::getFocusedComponent() {
	return focused_component;
}

paint_tool::Component *paint_tool::ComponentGroup::getComponent(const std::string &id) {

	Component *component = nullptr;

	auto it = components.find(id);

	if (it != components.end())
		component = it->second.get();

	return component;
}