#include "UIComboBox.h"
#include "../UIManager.h"

UIComboBox::UIComboBox(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName) :
	UIElement(parent, id, size, elementName),
	m_SelectionColour(sf::Color(200, 235, 245, 255)),
	m_SelectionPressed(-1)
{

}

UIComboBox::~UIComboBox()
{

}

void UIComboBox::implInitialise()
{
	m_Renderable->pickElement("None");
	/*m_Renderable->setDualRender(true);
	m_Renderable->f_RenderOverride = std::bind(&UIComboBox::renderCallback, this, 
		std::placeholders::_1, std::placeholders::_2);*/

	UIEventTable.connectOnExitedEvent(std::bind(&UIComboBox::dropdownReleased, this, 
		std::placeholders::_1));

	float width  = std::max(200.0f, m_Size.x);
	float height = std::max(34.0f, m_Size.y);
	setSize(width, height);

	m_InputElement = new UIElement(this, getID() + "_input", sf::Vector2f(200.0f, 26.0f), "_input");
	m_ParentManager->addElement(m_InputElement);
	m_InputElement->getRenderable()->pickElement("InputBox");
	m_InputElement->setPosition(sf::Vector2f(0.0f, 0.0f));

	m_DropdownBtn = new UIButton(this, getID() + "_dropdown", sf::Vector2f(24.0f, 14.0f), "dropdown");
	m_DropdownBtn->setDefaultElement("DropdownDefault");
	m_DropdownBtn->setPressedElement("DropdownPressed");
	m_ParentManager->addElement(m_DropdownBtn);

	m_DropdownBtn->UIEventTable.connectOnPressedEvent(std::bind(&UIComboBox::dropdownPressed, this, 
		std::placeholders::_1, std::placeholders::_2));

	m_CurrentSelection = new UIStaticLabel(this, getID() + "_selection", "");
	m_ParentManager->addElement(m_CurrentSelection);
	m_CurrentSelection->setText("", sf::Color::Black);
	m_CurrentSelection->setPosition(sf::Vector2f(8.0f, 5.0f));

	float sizeX = m_DropdownBtn->getRenderable()->getDimensions().x;
	float sizeY = m_DropdownBtn->getRenderable()->getDimensions().y;
	
	m_DropdownBtn->setPosition(sf::Vector2f(m_Size.x - sizeX - 6.0f, 5.0f));
	m_DropdownBtn->setSize(sizeX, sizeY);

	m_HeaderElement = new UIElement(this, getID() + "_header", sf::Vector2f(200.0f, 5.0f), "_header");
	m_ParentManager->addElement(m_HeaderElement);
	m_HeaderElement->getRenderable()->pickElement("ComboElementHeader");
	m_HeaderElement->setPosition(sf::Vector2f(0.0f, 26.0f));
	m_HeaderElement->hide();

	m_FooterElement = new UIElement(this, getID() + "_footer", sf::Vector2f(200.0f, 5.0f), "_footer");
	m_ParentManager->addElement(m_FooterElement);
	m_FooterElement->getRenderable()->pickElement("ComboElementFooter");
	m_FooterElement->setPosition(sf::Vector2f(0.0f, 31.0f));
	m_FooterElement->hide();
}

void UIComboBox::implUpdate()
{

}

void UIComboBox::acceptListener(UIElement* element, int32_t eventID)
{
	if (eventID == LISTEN_PRESSED)
	{
		for (int32_t i = 0; i < m_SelectionElements.size(); i++)
		{
			if (element == m_SelectionElements[i])
			{
				m_SelectionPressed = i;
				dropdownClose();
			}
		}
	}
}

void UIComboBox::setPosition(const sf::Vector2f& point)
{
	UIElement::setPosition(point);
}

void UIComboBox::addSelection(std::string text)
{
	UIElement* element = new UIElement(this, getID() + "_element", sf::Vector2f(200.0f, 14.0f), "_element");
	m_ParentManager->addElement(element);
	element->getRenderable()->pickElement("ComboElement");
	element->setPosition(sf::Vector2f(0.0f, 14.0f * m_SelectionList.size() + 31.0f));
	element->hide();
	element->listen(this, LISTEN_PRESSED);

	UIStaticLabel* label = new UIStaticLabel(this, getID() + "_selection", "_selection");
	m_ParentManager->addElement(label);
	label->setText(text, sf::Color::Black, 12U);
	label->setPosition(sf::Vector2f(6.0f, (14.0f * m_SelectionList.size()) + 31.0f));
	label->hide();
	label->setCanEnter(false);

	m_SelectionList.push_back(label);
	m_SelectionElements.push_back(element);

	sf::Vector2f new_position;
	new_position.x = m_FooterElement->getPosition().x;
	new_position.y = 31.0f;

	for (auto element : m_SelectionElements)
		new_position.y += element->getRenderable()->getDimensions().y;

	m_FooterElement->setPosition(new_position);
	m_StoredColour = m_SelectionElements[0]->getRenderable()->getColor();

	element->UIEventTable.connectOnEnteredEvent(std::bind(&UIComboBox::selectionEntered, this, std::placeholders::_1));
	element->UIEventTable.connectOnExitedEvent(std::bind(&UIComboBox::selectionExited, this, std::placeholders::_1));
}

void UIComboBox::setCharacterSize(uint32_t size)
{

}

void UIComboBox::setSelectionColour(sf::Color colour)
{
	m_SelectionColour = colour;
}

void UIComboBox::dropdownPressed(UIElement* element, sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		if (m_HeaderElement->isActive())
			dropdownClose();
		else
			dropdownOpen();
	}
}

void UIComboBox::dropdownReleased(UIElement* element)
{
	dropdownClose();
}

void UIComboBox::renderCallback(Renderable* renderable, sf::RenderTarget& target)
{
	sf::RectangleShape shape;
	shape.setSize(getSize());
	shape.setPosition(m_PositionAbsolute);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::Red);
	target.draw(shape);
}

void UIComboBox::selectionEntered(UIElement* element)
{
	element->getRenderable()->setColor(m_SelectionColour);

	for (int32_t i = 0; i < m_SelectionElements.size(); i++)
	{
		if (element == m_SelectionElements[i])
		{
			std::string text = m_SelectionList[i]->getText();
			m_CurrentSelection->setText(m_SelectionList[i]->getText(), sf::Color::Black);
		}
	}
}

void UIComboBox::selectionExited(UIElement* element)
{
	element->getRenderable()->setColor(m_StoredColour);
}

void UIComboBox::dropdownOpen()
{
	float width = getSize().x;
	float height = m_InputElement->getRenderable()->getDimensions().y;

	height += m_HeaderElement->getRenderable()->getDimensions().y;
	height += m_FooterElement->getRenderable()->getDimensions().y;

	for (auto compare : m_SelectionElements)
		height += compare->getRenderable()->getDimensions().y;

	setSize(width, height);

	m_HeaderElement->show();
	m_FooterElement->show();

	for (int32_t i = 0; i < m_SelectionList.size(); i++)
	{
		m_SelectionList[i]->show();
		m_SelectionElements[i]->show();
	}
}

void UIComboBox::dropdownClose()
{
	float width = getSize().x;
	float height = m_InputElement->getRenderable()->getDimensions().y;
	setSize(width, height);

	m_HeaderElement->hide();
	m_FooterElement->hide();

	for (int32_t i = 0; i < m_SelectionList.size(); i++)
	{
		m_SelectionList[i]->hide();
		m_SelectionElements[i]->hide();
	}

	if (m_SelectionPressed == -1)
		m_CurrentSelection->setText("", sf::Color::Black);
	else if (m_SelectionPressed > 0)
		m_CurrentSelection->setText(m_SelectionList[m_SelectionPressed]->getText(), sf::Color::Black);
}
