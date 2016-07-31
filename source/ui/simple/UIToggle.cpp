#include "UIToggle.h"

UIToggle::UIToggle(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName) :
	UIButton(parent, id, size, elementName)
{
}

UIToggle::~UIToggle()
{
}

void UIToggle::implInitialise()
{
	UIButton::implInitialise();
}

void UIToggle::implUpdate()
{
}

void UIToggle::setPressed(bool flag)
{
	UIElement::setPressed(flag);

	if (m_Pressed)
	{
		m_IsToggled = !m_IsToggled;

		if (m_IsToggled)
			m_Renderable->pickElement("ButtonToggled");
		else
			m_Renderable->pickElement("ButtonDefault");
	}
}

void UIToggle::setEntered(bool flag)
{
	UIElement::setEntered(flag);
}
