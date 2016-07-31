#include "UIStaticLabel.h"
#include "../../common/ResourceManager.h"

UIStaticLabel::UIStaticLabel(UIElement * parent, std::string id, std::string elementName) :
	UIElement(parent, id, sf::Vector2f(), elementName),
	m_FontName("kenvector_thin")
{
}

UIStaticLabel::~UIStaticLabel()
{
}

void UIStaticLabel::implInitialise()
{
	m_Renderable->pickElement("None");
	m_Renderable->setDualRender(true);
	m_Renderable->f_RenderOverride = std::bind(&UIStaticLabel::renderCallback, this,
		std::placeholders::_1, std::placeholders::_2);
}

void UIStaticLabel::implUpdate()
{
}

void UIStaticLabel::setPosition(const sf::Vector2f & point)
{
	UIElement::setPosition(point);

	if (m_StaticText)
		m_StaticText->setPosition(m_PositionAbsolute);
}

void UIStaticLabel::setText(std::string text, sf::Color colour, uint32_t size)
{
	sf::Font& font = *ResourceManager::instance().lookupFont(m_FontName);
	
	if (!m_StaticText)
	{
		m_StaticText = new sf::Text(text, font, size);
		m_StaticText->setColor(colour);
		m_StaticText->setStyle(sf::Text::Style::Bold);
	}
	else
	{
		m_StaticText->setString(text);
		m_StaticText->setColor(colour);
		m_StaticText->setCharacterSize(size);
		m_StaticText->setFont(font);
	}

	float width  = m_StaticText->getLocalBounds().width;
	float height = m_StaticText->getLocalBounds().height;

	setSize(sf::Vector2f(width, height));
}

void UIStaticLabel::setFont(std::string font)
{
	m_FontName = font;
	sf::Font& fnt = *ResourceManager::instance().lookupFont(m_FontName);

	if (m_StaticText)
		m_StaticText->setFont(fnt);
}

void UIStaticLabel::renderCallback(Renderable * renderable, sf::RenderTarget & target)
{
	if (m_StaticText)
		target.draw(*m_StaticText);
}
