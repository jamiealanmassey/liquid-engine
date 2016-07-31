#include "UIManager.h"

UIManager::UIManager(GameScene* scene, std::string skin, std::string skin_data) :
	m_Skin(skin),
	m_SkinData(skin_data),
	m_FocusedElement(nullptr),
	m_EnteredElement(nullptr),
	m_ParentScene(scene)
{
}

UIManager::~UIManager()
{
}

void UIManager::update(EventData data)
{
	// Update each UI element
	for (auto element : m_Elements)
		element->update();

	// Update the entered elements lists
	updateEntered(data);

	// If the mouse button was pressed
	if (data.mouse_button_pressed)
	{
		if (data.data_mouse_pressed == sf::Mouse::Button::Left && m_EnteredElement)
		{
			// Find the correct selection from the last entered element
			UIElement* selection = findNextInside(m_EnteredElement, data.data_mouse_pos);
		
			// If no child selection was found assign it as the primary
			// entered element
			if (selection == nullptr)
				selection = m_EnteredElement;

			// Make sure the button is active (i.e. not hidden or disabled)
			if (selection->isActive())
			{
				// Update mouse pressed position
				selection->setPositionPressedAbs(data.data_mouse_pos);
				selection->setPositionPressed(data.data_mouse_pos - selection->getPositionAbsolute());

				// Call the onPressed function for the selection and set it as focus
				selection->UIEventTable.callOnPressed(selection, data.data_mouse_pressed);
				selection->setFocus(true);
				selection->setPressed(true);

				// Trigger the transition if it exists
				if (selection->UITransitionTable.exists(UITRANSITION_PRESSED))
					selection->UITransitionTable.trigger(UITRANSITION_PRESSED);
			}

			// If the selection can accept focus and is focused then assign
			// the focused element to the selection
			if (selection->canAcceptFocus() && selection->hasFocus())
				m_FocusedElement = selection;
		}
		else if (data.data_mouse_pressed == sf::Mouse::Button::Right)
		{
			if (m_FocusedElement)
			{
				m_FocusedElement->setFocus(false);
				m_FocusedElement = nullptr;
			}
		}
	}

	// Otherwise if the mouse has been released
	else if (data.mouse_button_released)
	{
		// If there is an entered element and the left button was released do a button
		// pressed check
		if (data.data_mouse_released == sf::Mouse::Button::Left && m_EnteredElement)
			buttonPressedCheck(m_EnteredElement, data.data_mouse_released);

		// "" except with the focused element
		if (data.data_mouse_released == sf::Mouse::Button::Left && m_FocusedElement)
			buttonPressedCheck(m_FocusedElement, data.data_mouse_released);
	}

	// Check to see if the mouse has been moved and if we have an enetered element
	if (data.mouse_moved && m_FocusedElement)
	{
		// If the entered element is pressed call OnMoved event
		if (m_FocusedElement->isPressed())
			m_FocusedElement->UIEventTable.callOnMoved(m_FocusedElement, data.data_mouse_pos);

		// Do the same for all of the elements children
		for (auto child : m_FocusedElement->getChildren())
		{
			if (child->isPressed())
				child->UIEventTable.callOnMoved(child, data.data_mouse_pos);
		}
	}
}

void UIManager::updateEntered(EventData data)
{
	// If there was an entered element last frame check if we are still inside 
	// of it, if that is no longer the case disconnect it
	if (m_EnteredElement && !m_EnteredElement->isInside(data.data_mouse_pos))
	{
		for (auto child : m_EnteredElement->getChildren())
		{
			child->UIEventTable.callOnExited(child);
			child->setEntered(false);
		}

		if (m_EnteredElement->canLoseFocus())
			buttonPressedCheck(m_EnteredElement, data.data_mouse_pressed);

		m_EnteredElement->UIEventTable.callOnExited(m_EnteredElement);
		m_EnteredElement->setEntered(false);
		m_EnteredElement = nullptr;
	}
	else if (m_EnteredElement)
	{
		for (auto child : m_EnteredElement->getChildren())
		{
			bool inside = child->isInside(data.data_mouse_pos);

			if (!inside && child->isEntered())
			{
				child->UIEventTable.callOnExited(child);
				child->setEntered(false);
			}
			else if (inside && child->isEntered() && child->isPressed())
				child->UIEventTable.callOnMoved(child, data.data_mouse_pos);
		}
	}

	// Vector to store list of all entered elements
	std::vector<UIElement*> entered;

	// Iterate through each element and check if it has been entered,
	// if it has add it to entered vector
	std::vector<UIElement*>::reverse_iterator it = m_Elements.rbegin();
	for (; it != m_Elements.rend(); ++it)
	{
		if ((*it)->isActive() && (*it)->isEnabled() &&
			(*it)->isInside(data.data_mouse_pos) &&
			(*it)->canEnter())
		{
			entered.push_back(*it);
		}
	}

	// If we have at least one entered element in the pool
	if (!entered.empty())
	{
		// Create variable to find singular entered
		UIElement* findEntered = nullptr;

		// If the first entered has a parent use the findNextParent function
		// to climb the tree and find highest level intersecting element
		if (entered[0]->getParent())
			findEntered = findNextParent(entered[0], data.data_mouse_pos);

		// If no element was found set it to default element
		if (findEntered == nullptr)
			findEntered = entered[0];

		// Connect the newly entered element
		m_EnteredElement = findEntered;
		m_EnteredElement->UIEventTable.callOnEntered(m_EnteredElement);
		m_EnteredElement->setEntered(true);

		for (auto child : m_EnteredElement->getChildren())
		{
			if (child->isInside(data.data_mouse_pos))
			{
				child->UIEventTable.callOnEntered(child);
				child->setEntered(true);
			}
		}
	}
}

void UIManager::updateDestroyed()
{
	UIElement::ElementList::iterator itr = m_Elements.begin();

	for (; itr != m_Elements.end(); ++itr)
	{
		// TODO: Check that any effects are finished
		if ((*itr)->isDestroyNextFrame())
		{
			itr = m_Elements.erase(itr);
			
			if (itr == m_Elements.end())
				break;
		}
	}
}

void UIManager::addElement(UIElement* element)
{
	// First make sure element doesn't already exist in manager
	for (auto e : m_Elements)
	{
		if (e == element)
			return;
	}

	// Set manager, parent scene and initialise the element
	element->setParentManager(this);
	element->setParentScene(m_ParentScene);
	element->initialise();

	// Add any children elements to the manager if they aren't
	// already in it
	addElement(element->getChildren());
	m_Elements.push_back(element);
}

void UIManager::addElement(std::vector<UIElement*> elements)
{
	// Call down to addElement for each passed element
	for (auto element : elements)
		addElement(element);
}

void UIManager::removeElement(UIElement* element)
{
	UIElement::ElementList::iterator itr = m_Elements.begin();
	for (; itr != m_Elements.end(); ++itr)
	{
		if ((*itr) == element)
		{
			itr = m_Elements.erase(itr);
			break;
		}
	}
}

void UIManager::removeElement(std::string id)
{
	UIElement::ElementList::iterator itr = m_Elements.begin();
	for (; itr != m_Elements.end(); ++itr)
	{
		if ((*itr)->getID() == id)
		{
			itr = m_Elements.erase(itr);
			break;
		}
	}
}

void UIManager::buttonPressedCheck(UIElement* element, sf::Mouse::Button button)
{
	if (element->isPressed())
	{
		element->setPressed(false);
		element->UIEventTable.callOnReleased(element, button);

		if (element->UITransitionTable.exists(UITRANSITION_RELEASED))
			element->UITransitionTable.trigger(UITRANSITION_RELEASED);
	}
}

UIElement* UIManager::findNextInside(UIElement* element, const sf::Vector2f& point)
{
	// Store a copy of this element's children and store next selection
	UIElement::ElementList& children  = element->getChildren();
	UIElement*				selection = nullptr;

	// Search through every child element, if the mouse is inside of it then
	// also search its children for a selection
	for (int32_t i = children.size() - 1; i >= 0; i--)
	{
		if (children[i]->isInside(point) && children[i]->canEnter())
		{
			if (!children[i]->getChildren().empty())
				selection = findNextInside(children[i], point);
			else
				return children[i];
		}
	}

	if (selection == nullptr)
		selection = element;

	// Give the found result (null/UIElement*)
	return selection;
}

UIElement* UIManager::findNextParent(UIElement* element, const sf::Vector2f& point)
{
	// Variable to store next parent to be returned
	UIElement* nextParent = nullptr;

	// Check if this element has a parent, if it does check that the given
	// point is inside of it, if it is call this function recursively
	if (element->getParent() && element->getParent()->isInside(point) && element->canEnter())
		nextParent = findNextParent(element->getParent(), point);

	// If next parent is null then set it to this element and return it
	// as the top of the heirarchy
	if (nextParent == nullptr)
		nextParent = element;

	// Give result
	return nextParent;
}
