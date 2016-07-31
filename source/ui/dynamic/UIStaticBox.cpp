#include "UIStaticBox.h"
#include "../UIManager.h"

UIStaticBox::UIStaticBox(UIElement * parent, std::string id, sf::Vector2f size, std::string elementName) :
	UIElement(parent, id, size, elementName)
{
}

UIStaticBox::~UIStaticBox()
{
}

void UIStaticBox::implInitialise()
{
	getRenderable()->pickElement("None");

	// Instantiate the elements
	m_StaticTopLeft   = new UIElement(this, getID() + "_top_left", sf::Vector2f(), "_top_left");
	m_StaticTopRight  = new UIElement(this, getID() + "_top_right", sf::Vector2f(), "_top_right");
	m_StaticTopMiddle = new UIElement(this, getID() + "_top_middle", sf::Vector2f(), "_top_middle");
	m_StaticBtmMiddle = new UIElement(this, getID() + "_btm_middle", sf::Vector2f(), "_btm_middle");
	m_StaticLeft	  = new UIElement(this, getID() + "_left", sf::Vector2f(), "_left");
	m_StaticRight	  = new UIElement(this, getID() + "_right", sf::Vector2f(), "_right");
	m_StaticBtmLeft   = new UIElement(this, getID() + "_btm_left", sf::Vector2f(), "_btm_left");
	m_StaticBtmRight  = new UIElement(this, getID() + "_btm_right", sf::Vector2f(), "_btm_right");

	// Register the elements as UIElements in the UIManager
	m_ParentManager->addElement(m_StaticTopLeft);
	m_ParentManager->addElement(m_StaticTopRight);
	m_ParentManager->addElement(m_StaticTopMiddle);
	m_ParentManager->addElement(m_StaticBtmMiddle);
	m_ParentManager->addElement(m_StaticLeft);
	m_ParentManager->addElement(m_StaticRight);
	m_ParentManager->addElement(m_StaticBtmLeft);
	m_ParentManager->addElement(m_StaticBtmRight);

	// Give the elements renderables
	m_StaticTopLeft->getRenderable()->pickElement("StaticTopLeft");
	m_StaticTopRight->getRenderable()->pickElement("StaticTopRight");
	m_StaticTopMiddle->getRenderable()->pickElement("StaticTopMiddle");
	m_StaticBtmMiddle->getRenderable()->pickElement("StaticBtmMiddle");
	m_StaticLeft->getRenderable()->pickElement("StaticLeft");
	m_StaticRight->getRenderable()->pickElement("StaticRight");
	m_StaticBtmLeft->getRenderable()->pickElement("StaticBtmLeft");
	m_StaticBtmRight->getRenderable()->pickElement("StaticBtmRight");

	reconfigure();
}

void UIStaticBox::implUpdate()
{
}

void UIStaticBox::setSize(float x, float y)
{
	UIElement::setSize(x, y);
	reconfigure();
}

void UIStaticBox::setSize(const sf::Vector2f & point)
{
	UIElement::setSize(point);
	reconfigure();
}

void UIStaticBox::setColour(sf::Color colour)
{
	m_StaticTopLeft->getRenderable()->setColor(colour);
	m_StaticTopRight->getRenderable()->setColor(colour);
	m_StaticBtmLeft->getRenderable()->setColor(colour);
	m_StaticBtmRight->getRenderable()->setColor(colour);
	m_StaticTopMiddle->getRenderable()->setColor(colour);
	m_StaticBtmMiddle->getRenderable()->setColor(colour);
	m_StaticLeft->getRenderable()->setColor(colour);
	m_StaticRight->getRenderable()->setColor(colour);
}

void UIStaticBox::reconfigure()
{
	// Calculate required sizes to position
	sf::Vector2f content_size = m_StaticTopLeft->getRenderable()->getDimensions();
	sf::Vector2f left_corner_size = m_StaticTopLeft->getRenderable()->getDimensions();
	sf::Vector2f right_corner_size = m_StaticTopRight->getRenderable()->getDimensions();
	sf::Vector2f left_size = m_StaticLeft->getRenderable()->getDimensions();
	sf::Vector2f right_size = m_StaticRight->getRenderable()->getDimensions();

	float calc_width = m_Size.x - right_corner_size.x;
	float calc_height = m_Size.y - left_corner_size.y;
	float calc_x = (m_Size.x - left_size.x - right_size.x) / content_size.x;
	float calc_y = (m_Size.y - left_size.y - right_size.y) / content_size.y;

	// Apply positioning to each titlebar element
	m_StaticTopLeft->setPosition(0.0f, 0.0f);
	m_StaticTopRight->setPosition(calc_width, 0.0f);
	m_StaticBtmLeft->setPosition(0.0f, calc_height);
	m_StaticBtmRight->setPosition(calc_width, calc_height);
	m_StaticTopMiddle->setPosition(left_corner_size.x, 0.0f);
	m_StaticBtmMiddle->setPosition(left_corner_size.x, calc_height);
	m_StaticLeft->setPosition(0.0f, left_corner_size.y);
	m_StaticRight->setPosition(calc_width, right_corner_size.y);

	// Scale content element size accordingly
	m_StaticTopMiddle->getRenderable()->setScale(calc_x, 1.0f);
	m_StaticBtmMiddle->getRenderable()->setScale(calc_x, 1.0f);
	m_StaticLeft->getRenderable()->setScale(1.0f, calc_y);
	m_StaticRight->getRenderable()->setScale(1.0f, calc_y);
}
