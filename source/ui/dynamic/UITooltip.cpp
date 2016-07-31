#include "UITooltip.h"
#include "../UIManager.h"
#include <sstream>
#include <iostream>

UITooltip::UITooltip(UIElement * parent, std::string id, sf::Vector2f size, std::string elementName)
{
}

UITooltip::~UITooltip()
{
}

void UITooltip::implInitialise()
{
	m_RenderableText = new RenderableText();
	m_RenderableText->setFont("kenvector");
	m_RenderableText->setCharacterSize(11U);
	m_RenderableText->setPadding(18.0f, 18.0f);

	instantiateFrame();

	m_Renderable->pickElement("FrameSurface");
	m_Renderable->setDualRender(true);
	m_Renderable->f_RenderOverride = std::bind(&UITooltip::renderCallback, this,
		std::placeholders::_1, std::placeholders::_2);
}

void UITooltip::implUpdate()
{
}

void UITooltip::instantiateFrame()
{
	UIElement* topleft = new UIElement(this, getID() + "_topleft", sf::Vector2f(16.0f, 16.0f), "_topleft");
	UIElement* frmleft = new UIElement(this, getID() + "_frmleft", sf::Vector2f(16.0f, 16.0f), "_frmleft");
	UIElement* btmleft = new UIElement(this, getID() + "_btmleft", sf::Vector2f(16.0f, 16.0f), "_btmleft");
	UIElement* btmmidl = new UIElement(this, getID() + "_btmmidl", sf::Vector2f(16.0f, 16.0f), "_btmmidl");
	UIElement* btmrght = new UIElement(this, getID() + "_btmrght", sf::Vector2f(16.0f, 16.0f), "_btmrght");
	UIElement* frright = new UIElement(this, getID() + "_frright", sf::Vector2f(16.0f, 16.0f), "_frright");
	UIElement* toprght = new UIElement(this, getID() + "_toprght", sf::Vector2f(16.0f, 16.0f), "_toprght");
	UIElement* topmidl = new UIElement(this, getID() + "_frmmidl", sf::Vector2f(16.0f, 16.0f), "_frmmidl");
	//UIElement* frsurfc = new UIElement(this, getID() + "_frsurfc", sf::Vector2f(16.0f, 16.0f), "_frsurfc");

	m_TooltipFrame.push_back(topleft);
	m_TooltipFrame.push_back(frmleft);
	m_TooltipFrame.push_back(btmleft);
	m_TooltipFrame.push_back(btmmidl);
	m_TooltipFrame.push_back(btmrght);
	m_TooltipFrame.push_back(frright);
	m_TooltipFrame.push_back(toprght);
	m_TooltipFrame.push_back(topmidl);

	for (auto frame_element : m_TooltipFrame)
		m_ParentManager->addElement(frame_element);

	topleft->getRenderable()->pickElement("FrameTopLeft");
	frmleft->getRenderable()->pickElement("FrameLeft");
	btmleft->getRenderable()->pickElement("FrameBtmLeft");
	btmmidl->getRenderable()->pickElement("FrameBtmMiddle");
	btmrght->getRenderable()->pickElement("FrameBtmRight");
	frright->getRenderable()->pickElement("FrameRight");
	toprght->getRenderable()->pickElement("FrameTopRight");
	topmidl->getRenderable()->pickElement("FrameTopMiddle");
	//frsurfc->getRenderable()->pickElement("FrameSurface");

	updateFrame();
}

void UITooltip::updateFrame()
{
	sf::FloatRect bounds = m_RenderableText->getLocalBounds();

	float new_x = 0.0f;
	float new_y = 0.0f;

	new_x = (bounds.width - 16.0f) / m_TooltipFrame[3]->getRenderable()->getDimensions().x;
	m_TooltipFrame[3]->getRenderable()->setScale(new_x, 1.0f);

	new_x = (bounds.width - 16.0f) / m_TooltipFrame[7]->getRenderable()->getDimensions().x;
	m_TooltipFrame[7]->getRenderable()->setScale(new_x, 1.0f);

	new_y = (bounds.height - 16.0f) / m_TooltipFrame[1]->getRenderable()->getDimensions().y;
	m_TooltipFrame[1]->getRenderable()->setScale(1.0f, new_y);

	new_y = (bounds.height - 16.0f) / m_TooltipFrame[5]->getRenderable()->getDimensions().y;
	m_TooltipFrame[5]->getRenderable()->setScale(1.0f, new_y);



	float full_width  = m_TooltipFrame[2]->getRenderable()->getDimensions().x + 
						m_TooltipFrame[3]->getRenderable()->getDimensions().x;

	float full_height = m_TooltipFrame[0]->getRenderable()->getDimensions().y + 
						m_TooltipFrame[1]->getRenderable()->getDimensions().y;

	m_TooltipFrame[0]->setPosition(1.0f, 0.0f);
	m_TooltipFrame[1]->setPosition(1.0f, 8.0f);
	m_TooltipFrame[2]->setPosition(1.0f, bounds.height - 8.0f);
	m_TooltipFrame[3]->setPosition(8.0f, bounds.height - 8.0f);
	m_TooltipFrame[4]->setPosition(bounds.width - 8.0f, bounds.height - 8.0f);
	m_TooltipFrame[5]->setPosition(bounds.width - 8.0f, 8.0f);
	m_TooltipFrame[6]->setPosition(bounds.width - 9.0f, 0.0f);
	m_TooltipFrame[7]->setPosition(8.0f, 0.0f);

	float centre_x = (bounds.width - 16.0f) / m_Renderable->getDimensions().x;
	float centre_y = (bounds.height - 16.0f) / m_Renderable->getDimensions().y;

	m_Renderable->setPosition(m_PositionAbsolute + sf::Vector2f(8.0f, 8.0f));
	m_Renderable->setScale(centre_x, centre_y);
}

void UITooltip::setPressed(bool flag)
{
	UIElement::setPressed(flag);
}

void UITooltip::setEntered(bool flag)
{
	UIElement::setEntered(flag);
}

void UITooltip::setPosition(const sf::Vector2f& point)
{
	UIElement::setPosition(point);

	if (m_RenderableText)
		m_RenderableText->setPosition(m_PositionAbsolute);

	updateFrame();
}

void UITooltip::setTooltipText(const std::string text)
{
	m_RenderableText->setString(text);

	setSize(m_RenderableText->getLocalBounds().width, 
			m_RenderableText->getLocalBounds().height);

	updateFrame();
}

void UITooltip::renderCallback(Renderable* renderable, sf::RenderTarget & target)
{
	if (m_Active)
		m_RenderableText->draw(target, sf::RenderStates());

	/*sf::RectangleShape shape;
	sf::FloatRect bounds = m_RenderableText->getLocalBounds();

	shape.setPosition(m_PositionAbsolute);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.0f);
	shape.setSize(getSize());

	target.draw(shape);*/
}

