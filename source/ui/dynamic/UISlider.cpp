#include "UISlider.h"
#include "../UIManager.h"

UISlider::UISlider(UIElement * parent, std::string id, sf::Vector2f size, std::string elementName) :
	UIElement(parent, id, size, elementName),
	m_Type(eSliderType::SLIDER_HORIZONTAL)
{
}

UISlider::~UISlider()
{
}

void UISlider::implInitialise()
{
	// Create a new hanging background element for the slider
	m_Element = new UIElement(this, getID() + "_element", sf::Vector2f(), "_element");
	m_ParentManager->addElement(m_Element);
	m_Element->setCanEnter(false);

	// Make a pointer that we can interact with to give a slider value
	m_Pointer = new UIElement(this, getID() + "_pointer", sf::Vector2f(), "_pointer");
	m_ParentManager->addElement(m_Pointer);

	// Depending on the slider type setup our new elements
	if (m_Type == eSliderType::SLIDER_HORIZONTAL)
	{
		m_Element->getRenderable()->pickElement("SliderHorizontal");
		m_Pointer->getRenderable()->pickElement("SliderPHorizontal");

		float scale_x = m_Size.x / m_Element->getRenderable()->getDimensions().x;
		m_Element->getRenderable()->setScale(scale_x, 1.0f);

		m_Element->setSize(sf::Vector2f(m_Size.x, m_Element->getRenderable()->getDimensions().y));
		m_Pointer->setSize(m_Pointer->getRenderable()->getDimensions());

		setSize(m_Size.x + m_Pointer->getSize().x, m_Pointer->getRenderable()->getDimensions().y + 10.0f);
		m_Pointer->setPosition(m_Pointer->getPosition().x, (getSize().y / 2.0f) - (m_Pointer->getSize().y / 2.0f));
		m_Element->setPosition(sf::Vector2f(m_Pointer->getSize().x / 2.0f, 10.0f));
	}
	else if (m_Type == eSliderType::SLIDER_VERTICAL)
	{
		m_Element->getRenderable()->pickElement("SliderVertical");
		m_Pointer->getRenderable()->pickElement("SliderPVertical");

		float scale_y = m_Size.y / m_Element->getRenderable()->getDimensions().y;
		m_Element->getRenderable()->setScale(1.0f, scale_y);

		m_Element->setSize(sf::Vector2f(m_Element->getRenderable()->getDimensions().y, m_Size.y));
		m_Pointer->setSize(m_Pointer->getRenderable()->getDimensions());

		setSize(m_Pointer->getRenderable()->getDimensions().x,
			m_Element->getRenderable()->getDimensions().y);

		setSize(m_Pointer->getRenderable()->getDimensions().x + 10.0f, m_Size.y + m_Pointer->getSize().y);
		m_Pointer->setPosition((getSize().x / 2.0f) - (m_Pointer->getSize().x / 2.0f), m_Pointer->getPosition().y);
		m_Element->setPosition(sf::Vector2f(10.0f, m_Pointer->getSize().y / 2.0f));
	}

	// Bind rendering and set element to none
	m_Renderable->pickElement("None");
	m_Renderable->setDualRender(false);
	m_Renderable->f_RenderOverride = std::bind(&UISlider::renderCallback, this, 
		std::placeholders::_1, std::placeholders::_2);

	// Pass the pointer an OnMoved callback for when the mouse has been moved
	m_Pointer->UIEventTable.connectOnMovedEvent(std::bind(&UISlider::movedCallback, this, 
		std::placeholders::_1, std::placeholders::_2));
}

void UISlider::implUpdate()
{
}

void UISlider::setPressed(bool flag)
{
	UIElement::setPressed(flag);
}

void UISlider::setEntered(bool flag)
{
	UIElement::setEntered(flag);
}

void UISlider::setPosition(const sf::Vector2f & point)
{
	UIElement::setPosition(point);
}

void UISlider::setSliderType(eSliderType type)
{
	m_Type = type;

	// TODO: update slider rotation
}

void UISlider::movedCallback(UIElement * element, sf::Vector2f mouse_pos)
{
	// Get element dims and setup variables 
	sf::Vector2f element_dims = m_Element->getSize();
	float ratio, position_x, position_y, size;

	// Find new ratio and set pointer based on rotation
	if (m_Type == eSliderType::SLIDER_HORIZONTAL)
	{
		ratio = (mouse_pos.x - m_Element->getPositionAbsolute().x) / element_dims.x;
		size = m_Pointer->getSize().x / 2.0f;

		position_x = (element_dims.x * ratio);
		position_y = (getSize().y / 2.0f) - (m_Pointer->getSize().y / 2.0f);

		position_x = std::min(element_dims.x + size, position_x + size);
		position_x = std::max(0.0f, position_x - size);
	}
	else if (m_Type == eSliderType::SLIDER_VERTICAL)
	{
		ratio = (mouse_pos.y - m_Element->getPositionAbsolute().y) / element_dims.y;
		size = m_Pointer->getSize().y / 2.0f;

		position_x = (getSize().x / 2.0f) - (m_Pointer->getSize().x / 2.0f);
		position_y = (element_dims.y * ratio);

		position_y = std::min(element_dims.y + size, position_y + size);
		position_y = std::max(0.0f + 2.0f, position_y - size);
	}

	// Clamp the ratio between 0 and 1
	ratio = std::min(ratio, 1.0f);
	ratio = std::max(ratio, 0.0f);

	// Update ratio and pointer position
	m_Ratio = ratio;
	m_Pointer->setPosition(sf::Vector2f(position_x, position_y));

	std::cout << m_Ratio << std::endl;
}

void UISlider::renderCallback(Renderable* renderable, sf::RenderTarget & target)
{
	/*sf::RectangleShape shape;
	shape.setPosition(m_PositionAbsolute);
	shape.setSize(getSize());
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape);

	sf::RectangleShape shape2;
	shape2.setPosition(m_Pointer->getPositionAbsolute());
	shape2.setSize(m_Pointer->getSize());
	shape2.setOutlineThickness(1.0f);
	shape2.setOutlineColor(sf::Color::Green);
	shape2.setFillColor(sf::Color::Transparent);
	target.draw(shape2);*/
}
