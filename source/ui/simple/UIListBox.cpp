#include "UIListBox.h"
#include "../UIManager.h"
#include "../../utilities/Logger.h"

UIListBox::UIListBox(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName) :
	UIElement(parent, id, size, elementName),
	m_ListType(eListType::SINGLE),
	m_Padding(5.0f, 5.0f)
{
	m_FrameOutline.setFillColor(sf::Color::Black);
	m_FrameOutline.setOutlineColor(sf::Color(130, 130, 130, 255));
	m_FrameOutline.setOutlineThickness(1);
	m_CharacterSize = 12U;
}

UIListBox::~UIListBox()
{
}

void UIListBox::implInitialise()
{
	m_Renderable->pickElement("None");
	m_Renderable->setDualRender(true);
	m_Renderable->f_RenderOverride = std::bind(&UIListBox::renderCallback, this,
		std::placeholders::_1, std::placeholders::_2);
}

void UIListBox::implUpdate()
{
}

void UIListBox::acceptListener(UIElement * element, int32_t eventID)
{
	if (eventID == LISTEN_PRESSED)
	{
		int32_t index = getSelectedIndex(element);

		if (index == -1 && m_ListType == eListType::SINGLE)
		{
			m_SelectedItems.clear();
			m_SelectedItems.push_back(element);
		}
		else if (index == -1 && m_ListType == eListType::MULTIPLE)
			m_SelectedItems.push_back(element);
		else if (index != -1)
			m_SelectedItems.erase(m_SelectedItems.begin() + index);
	}
}

void UIListBox::setPosition(const sf::Vector2f& point)
{
	UIElement::setPosition(point);
	m_FrameOutline.setPosition(point);
}

void UIListBox::addItem(std::string text)
{
	UIStaticLabel* label = new UIStaticLabel(this, getID() + "_item", "_item");
	m_ParentManager->addElement(label);

	label->setFont("kenvector");
	label->setText(text, sf::Color::White, m_CharacterSize);
	label->setPosition(sf::Vector2f(m_Padding.x / 2.0f, m_ListItems.size() * (m_CharacterSize + 2.0f)));
	label->listen(this, LISTEN_PRESSED);
	m_ListItems.push_back(label);

	float width  = 0.0f;
	float height = 0.0f;

	for (auto next_text : m_ListItems)
	{
		width = std::max(next_text->getStaticText()->getLocalBounds().width + 4.0f, width);
		height += m_CharacterSize + 2.0f;
	}

	label->setSize(width, m_CharacterSize + 2.0f);
	setSize(width + m_Padding.x, height);
	m_FrameOutline.setSize(sf::Vector2f(width + m_Padding.x, height));
}

void UIListBox::setOutlineColour(sf::Color colour)
{
	// Assign the outline colour
	m_FrameOutline.setOutlineColor(colour);
}

void UIListBox::setCharacterSize(uint32_t size)
{
	m_CharacterSize = size;
	updateLabelPositions();
}

bool UIListBox::isItemSelected(UIElement* element)
{
	for (auto compare : m_SelectedItems)
	{
		if (compare == element)
			return true;
	}

	return false;
}

bool UIListBox::isItemSelected(int32_t index)
{
	if (index > m_ListItems.size())
	{
		std::string message;
		message += "isItemSelected(";
		message += std::to_string(index);
		message += ") called on UIListBox <";
		message += getID() + getName();
		message += "> with an index that is out of range.";

		return Logger::instance().message(message, Logger::eType::LOG_ERROR, false);
	}

	for (auto compare : m_SelectedItems)
	{
		if (compare == m_ListItems[index])
			return true;
	}

	return false;
}

std::vector<UIElement*> UIListBox::getSelectedItems()
{
	return m_SelectedItems;
}

void UIListBox::renderCallback(Renderable* renderable, sf::RenderTarget& target)
{
	// Draw outline around the List Box
	target.draw(m_FrameOutline);

	for (int32_t i = 0; i < m_SelectedItems.size(); i++)
	{
		UIStaticLabel* label_conv = static_cast<UIStaticLabel*>(m_SelectedItems[i]);
		sf::Vector2f size;
		size.x = getSize().x;
		size.y = m_CharacterSize + 2.0f;

		sf::Vector2f calc_position;
		calc_position.x = -(m_Padding.x / 2.0f);
		calc_position.y = 0.0f;

		sf::RectangleShape shape;
		shape.setFillColor(sf::Color(50, 250, 50, 200));
		shape.setPosition(m_SelectedItems[i]->getPositionAbsolute() + calc_position);
		shape.setSize(size);
		target.draw(shape);
	}
}

void UIListBox::updateLabelPositions()
{
	for (int32_t i = 0; i < m_ListItems.size(); i++)
	{
		sf::Vector2f position;
		position.x = m_Padding.x / 2.0f;
		position.y = (i * m_CharacterSize + 2.0f);

		m_ListItems[i]->setPosition(position);
	}
}

int32_t UIListBox::getSelectedIndex(UIElement* element)
{
	for (int32_t i = 0; i < m_SelectedItems.size(); i++)
	{
		if (m_SelectedItems[i] == element)
			return i;
	}

	return -1;
}
