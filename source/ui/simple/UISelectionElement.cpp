#include "UISelectionElement.h"
#include "../../common/ResourceManager.h"
#include "../../common/GameScene.h"

UISelectionElement::UISelectionElement(UIElement * parent, std::string id, sf::Vector2f size, std::string elementName) :
	UIElement(parent, id, size, elementName),
	m_IsSelected(false),
	m_RadioLabel(nullptr)
{
}

UISelectionElement::~UISelectionElement()
{
}

void UISelectionElement::implInitialise()
{
	if (m_SelectionType == UISelectionBox::eSelectionType::RADIOBOX)
		m_Renderable->pickElement("RadioDefault");
	else if (m_SelectionType == UISelectionBox::eSelectionType::CHECKBOX)
		m_Renderable->pickElement("CheckDefault");

	m_Renderable->setDualRender(true);
	m_Renderable->f_RenderOverride = std::bind(&UISelectionElement::renderCallback, this,
		std::placeholders::_1, std::placeholders::_2);

	setSize(m_Renderable->getDimensions());

	m_RadioLabel = new UIStaticLabel(this, getID() + "Element", getID() + "Element");
	m_RadioLabel->listen(this, LISTEN_PRESSED);
	m_ParentScene->getUIManager()->addElement(m_RadioLabel);
}

void UISelectionElement::implUpdate()
{
}

void UISelectionElement::setPressed(bool flag)
{
	UIElement::setPressed(flag);

	if (m_Pressed)
		select();
}

void UISelectionElement::setEntered(bool flag)
{
	UIElement::setEntered(flag);
}

void UISelectionElement::acceptListener(UIElement* element, int32_t eventID)
{
	if (eventID == LISTEN_PRESSED)
	{
		select();
		static_cast<UISelectionBox*>(getParent())->setCurrentSelection(this);
	}
}

void UISelectionElement::setPosition(const sf::Vector2f & point)
{
	UIElement::setPosition(point);

	if (m_RadioLabel)
	{
		float relative_x = m_Renderable->getDimensions().x + 5.0f;
		float relative_y = 2.0f;

		m_RadioLabel->setPosition(sf::Vector2f(relative_x, relative_y));
	}
}

void UISelectionElement::setText(std::string text, sf::Color colour, uint32_t size)
{
	m_RadioLabel->setText(text, colour, size);	

	float width = m_Renderable->getDimensions().x + 5.0f + m_RadioLabel->getSize().x;
	float height = std::max(m_Renderable->getDimensions().y, m_RadioLabel->getSize().y);
	setSize(sf::Vector2f(width, height));
}

void UISelectionElement::setSelectionType(UISelectionBox::eSelectionType type)
{
	m_SelectionType = type;

	if (m_SelectionType == UISelectionBox::eSelectionType::CHECKBOX)
		m_Renderable->pickElement("CheckDefault");
	else if (m_SelectionType == UISelectionBox::eSelectionType::RADIOBOX)
		m_Renderable->pickElement("RadioDefault");
}

void UISelectionElement::select()
{
	if (m_SelectionType == UISelectionBox::eSelectionType::RADIOBOX)
	{
		if (m_IsSelected)
		{
			m_Renderable->pickElement("RadioDefault");
			m_IsSelected = false;
		}
		else
		{
			m_Renderable->pickElement("RadioSelect");
			m_IsSelected = true;
		}
	}
	else if (m_SelectionType == UISelectionBox::eSelectionType::CHECKBOX)
	{
		m_IsSelected = !m_IsSelected;
		m_IsSelected ? m_Renderable->pickElement("CheckSelect") :
					   m_Renderable->pickElement("CheckDefault");
	}
}

void UISelectionElement::deselect()
{
	if (m_SelectionType == UISelectionBox::eSelectionType::RADIOBOX)
	{
		m_IsSelected = false;
		m_Renderable->pickElement("RadioDefault");
	}
	else if (m_SelectionType == UISelectionBox::eSelectionType::CHECKBOX)
	{
		m_IsSelected = !m_IsSelected;
		m_IsSelected ? m_Renderable->pickElement("CheckSelect") :
					   m_Renderable->pickElement("CheckDefault");
	}
}

void UISelectionElement::renderCallback(Renderable * renderable, sf::RenderTarget & target)
{
}
