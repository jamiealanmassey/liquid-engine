#include "UIButton.h"
#include "../../common/ResourceManager.h"

UIButton::UIButton(UIElement * parent, std::string id, sf::Vector2f size, std::string elementName) :
	UIElement(parent, id, size, elementName),
	m_ButtonDefaultElement("ButtonDefault"),
	m_ButtonPressedElement("ButtonPressed"),
	m_DrawHover(true)
{
}

UIButton::~UIButton()
{
}

void UIButton::implInitialise()
{
	m_Renderable->pickElement(m_ButtonDefaultElement);
	m_Renderable->setDualRender(true);
	m_Renderable->f_RenderOverride = std::bind(&UIButton::renderEntered, this, 
		std::placeholders::_1, std::placeholders::_2);
}

void UIButton::implUpdate()
{
}

void UIButton::setPressed(bool flag)
{
	UIElement::setPressed(flag);

	if (m_Pressed)
		m_Renderable->pickElement(m_ButtonPressedElement);
	else
		m_Renderable->pickElement(m_ButtonDefaultElement);
}

void UIButton::setEntered(bool flag)
{
	UIElement::setEntered(flag);
}

void UIButton::setPosition(const sf::Vector2f& point)
{
	UIElement::setPosition(point);
	centreText();
}

void UIButton::setText(std::string text, sf::Color colour, uint32_t size)
{
	if (!m_ButtonText)
	{
		sf::Font& font = *ResourceManager::instance().lookupFont("kenvector_thin");
		m_ButtonText = new sf::Text(text, font, size);
		m_ButtonText->setColor(colour);
		m_ButtonText->setStyle(sf::Text::Style::Bold);

		fitTextSize();
		centreText();
	}
	else
	{
		m_ButtonText->setString(text);
		m_ButtonText->setColor(colour);
		m_ButtonText->setCharacterSize(size);

		fitTextSize();
		centreText();
	}
}

void UIButton::centreText()
{
	if (m_ButtonText && m_Renderable)
	{
		float width = m_ButtonText->getLocalBounds().width / 2.0f;
		float height = m_ButtonText->getLocalBounds().height / 2.0f;
		float width2 = m_Renderable->getDimensions().x / 2.0f;
		float height2 = m_Renderable->getDimensions().y / 3.0f;

		float position_x = width2 - width;
		float position_y = height2 - height;

		m_ButtonText->setPosition(getPositionAbsolute() + sf::Vector2f(position_x, position_y));
	}
}

void UIButton::fitTextSize()
{
	if (m_Renderable && m_ButtonText)
	{
		float width  = m_ButtonText->getLocalBounds().width;
		float width2 = m_Renderable->getDimensions().x - 10.0f;

		if (width > width2)
		{
			uint32_t size = m_ButtonText->getCharacterSize() - 1;
			m_ButtonText->setCharacterSize(size);

			fitTextSize();
		}
	}
}

void UIButton::renderEntered(Renderable * renderable, sf::RenderTarget & target)
{
	if (m_ButtonText)
		target.draw(*m_ButtonText);

	if (m_Entered && m_DrawHover)
	{
		sf::RectangleShape shape;
		shape.setPosition(m_Renderable->getPosition());
		shape.setSize(m_Renderable->getDimensions());
		shape.setFillColor(sf::Color(0, 0, 0, 100));
		target.draw(shape);
	}
}
