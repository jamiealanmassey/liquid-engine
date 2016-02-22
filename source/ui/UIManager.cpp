#include "UIManager.h"
#include "../common/GameManager.h"

UIManager::UIManager(GameScene* scene_ptr) :
	m_FocusedElement(nullptr),
	m_FocusedElementLast(nullptr)
{
	m_ParentScene = scene_ptr;
}

UIManager::~UIManager()
{
}

void UIManager::update(float delta, EventData data)
{
	// Update elements
	for (auto e : m_Elements)
		e->update(delta);

	// Update entered and focused elements
	updateEntered(delta, data);
	updateFocused(delta, data);

	// If mouse button was pressed call down to all entered elements calling
	// corresponding functions and passing data
	if (data.mouse_button_pressed)
	{
		for (auto e : m_EnteredElements)
		{
			e->setPressed(true);
			e->onPressed(data.data_mouse_pressed);

			if (e->f_OnPressed)
				e->f_OnPressed(e, data.data_mouse_pressed);
		}
	}

	// If mouse button was pressed call down to all elements calling
	// corresponding functions and passing data
	if (data.mouse_button_released)
	{
		for (auto e : m_Elements)
		{
			if (e->checkPressed())
			{
				e->setPressed(false);
				e->onReleased(data.data_mouse_released);

				if (e->f_OnReleased)
					e->f_OnReleased(e, data.data_mouse_released);
			}
		}
	}

	// Iterate over elements and search for element to remove
	std::vector<UIElement*>::iterator it = m_Elements.begin();
	for (; it != m_Elements.end(); ++it)
	{
		if ((*it)->checkToDestroy())
		{
			it = m_Elements.erase(it);
			break;
		}
	}
}

void UIManager::updateEntered(float delta, EventData data)
{
	// Flush entered elements from last frame
	m_EnteredElements.clear();

	// Create temporary lists of elements for use in sampling and swapping data
	// while checking for entered elements
	std::list<UIElement*> reference1;
	std::list<UIElement*> reference2;
	std::list<UIElement*> reference3;

	// Iterate through each element and check if
	// 1) They are renderable
	// 2) They are intersected by the mouse
	for (auto e : m_Elements)
	{
		if (e->checkAllowInteraction() && e->getRenderable())
		{
			// Sample dimensions
			sf::Vector2f position = e->getPosition();
			sf::Vector2f dims	  = e->getRenderable()->getDimensions();
			sf::Vector2f mouse    = data.data_mouse_pos;

			// Evaluate intersection to a boolean value through checks
			bool intersection = (mouse.x > position.x && 
								 mouse.y > position.y &&
								 mouse.x < position.x + dims.x && 
								 mouse.y < position.y + dims.y);

			// If it does intersect add to reference1 list, otherwise add to
			// reference2 list
			intersection ? reference1.push_back(e) : 
						   reference2.push_back(e);
		}
	}

	// Compare elements that were entered last frame to elements that did not
	// get entered this frame, push them to reference3 list
	for (auto e1 : m_EnteredElementsLast)
	{
		for (auto e2 : reference2)
		{
			if (e1 == e2)
				reference3.push_back(e2);
		}
	}

	// Clear the entered elements last frame and add new entered elements
	m_EnteredElementsLast.clear();
	for (auto e : reference1)
		m_EnteredElementsLast.push_back(e);

	// Iterate through each element that was entered this frame and call relevant
	// entered functions
	for (auto e : reference1)
	{
		e->onEnter();
		e->setEntered(true);

		if (e->f_OnEntered)
			e->f_OnEntered(e);

		m_EnteredElements.push_back(e);
	}

	// Iterate through elements that were entered last frame and not enetered this frame
	// calling functions related to exiting
	for (auto e : reference3)
	{
		e->onExit();
		e->setEntered(false);

		if (e->f_OnExit)
			e->f_OnExit(e);
	}
}

void UIManager::updateFocused(float delta, EventData data)
{
	// If the mouse button has been pressed and the pressed button
	// was the left mouse button continue
	if (data.mouse_button_pressed && 
		(data.data_mouse_pressed == sf::Mouse::Button::Left))
	{
		// Iterate through each element, if it has been entered then we
		// can assume that the element is being focused
		for (auto e : m_Elements)
		{
			if (e->checkEntered())
			{
				// Switch elements
				m_FocusedElementLast = m_FocusedElement;
				m_FocusedElement     = e;

				// Make sure there was a last element
				if (m_FocusedElementLast != nullptr)
				{
					// Update flag to last element and call funcs
					m_FocusedElementLast->setFocused(false);
					m_FocusedElementLast->onDefocus();

					// Call to defocus() function ptr if it exists
					if (m_FocusedElementLast->f_OnDefocus)
						m_FocusedElementLast->f_OnDefocus(e);
				}

				// Make sure there is a focused element
				if (m_FocusedElement)
				{
					// Update flag to focused element and call funcs
					m_FocusedElement->setFocused(true);
					m_FocusedElement->onFocus();

					// Call to focus() function ptr if it exists
					if (m_FocusedElement->f_OnFocus)
						m_FocusedElement->f_OnFocus(e);
				}

				// Once we find one element, exit the function
				return;
			}
		}
	}
}

void UIManager::addElement(UIElement* element)
{
	// Make sure the element isn't a duplicate
	for (auto e : m_Elements)
	{
		if (e == element)
			return;
	}

	// Set the element's GameScene and add it to elements list
	element->setGameScene(m_ParentScene);
	element->init();
	m_Elements.push_back(element);

	// Add children too in-case
	for (auto e : element->getChildren())
		addElement(e);
}

void UIManager::addElement(std::vector<UIElement*> elements)
{
	// Iterate elements and call down to addElement(element)
	for (auto e : elements)
		addElement(e);
}

void UIManager::removeElement(UIElement* element)
{
	// DESTROY
	element->destroy();
}
