#include "UISelectionBox.h"
#include "UISelectionElement.h"

UISelectionBox::UISelectionBox(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName, eSelectionType type) :
	UIElement(parent, id, size, elementName),
	m_SelectionType(type),
	m_CurrentSelection(-1)
{
}

UISelectionBox::~UISelectionBox()
{
}

void UISelectionBox::implInitialise()
{
	m_Renderable->pickElement("None");
	m_Renderable->setDualRender(true);
	m_Renderable->f_RenderOverride = std::bind(&UISelectionBox::renderCallback, this,
		std::placeholders::_1, std::placeholders::_2);
}

void UISelectionBox::implUpdate()
{
}

void UISelectionBox::setPressed(bool flag)
{
	UIElement::setPressed(flag);
}

void UISelectionBox::setEntered(bool flag)
{
	UIElement::setEntered(flag);
}

void UISelectionBox::setPosition(const sf::Vector2f & point)
{
	UIElement::setPosition(point);
}

void UISelectionBox::acceptListener(UIElement* element, int32_t eventID)
{
	if (eventID == LISTEN_PRESSED)
		setCurrentSelection(element);
}

void UISelectionBox::addSelection(UISelectionElement * radioBtn)
{
	radioBtn->setSelectionType(m_SelectionType);
	radioBtn->listen(this, LISTEN_PRESSED);
	addChild(radioBtn);
	m_SelectionList.push_back(radioBtn);

	formatBox();
}

void UISelectionBox::addSelection(std::vector<UISelectionElement*> radioBtnList)
{
	for (auto radio_btn : radioBtnList)
		addSelection(radio_btn);
}

void UISelectionBox::setCurrentSelection(UIElement* element)
{
	if (m_SelectionType != eSelectionType::RADIOBOX)
		return;

	for (int i = 0; i < m_SelectionList.size(); i++)
	{
		if (m_SelectionList[i] == element)
		{
			if (m_CurrentSelection != -1)
				m_SelectionList[m_CurrentSelection]->select();

			m_CurrentSelection = i;
		}
	}
}

bool UISelectionBox::isSelected(int32_t index)
{
	return (m_SelectionList[index]->isSelected());
}

void UISelectionBox::formatBox()
{
	float next_y = 0.0f;

	for (auto element : m_SelectionList)
	{
		element->setPosition(sf::Vector2f(5.0f, next_y));

		float height = element->getSize().y + 5.0f;
		float width = element->getSize().x + 5.0f;
		next_y += height;
		//float next_y = m_Size.y + height;

		float checkWidth = std::max(m_Size.x, width);
		float checkHeight = std::max(m_Size.y, next_y);
		
		setSize(sf::Vector2f(checkWidth, checkHeight));
	}
}

void UISelectionBox::renderCallback(Renderable * renderable, sf::RenderTarget & target)
{
}
