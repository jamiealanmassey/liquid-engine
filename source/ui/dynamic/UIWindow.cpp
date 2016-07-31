#include "UIWindow.h"
#include "../UIManager.h"
#include "../../utilities/Vectors.h"

UIWindow::UIWindow(UIElement * parent, std::string id, sf::Vector2f size, std::string elementName, uint8_t windowFlags) :
	UIElement(parent, id, size, elementName),
	m_WindowFlags(windowFlags),
	m_RootPosition(0.0f),
	m_AllowMovement(false)
{
}

UIWindow::~UIWindow()
{
}

void UIWindow::implInitialise()
{
	// Make sure that the renderable isn't using a texture
	getRenderable()->pickElement("None");

	// Make sure focus cannot be lost by leaving intersection
	m_CanLoseFocus = false;

	// Call to construction helper funcs
	constructComparatives();
	constructTitlebar();
	constructWindow();

	// Bind on released callback
	UIEventTable.connectOnReleasedEvent(std::bind(&UIWindow::releasedCallback, this,
		std::placeholders::_1, std::placeholders::_2));

	// Bind on pressed callback
	UIEventTable.connectOnPressedEvent(std::bind(&UIWindow::pressedCallback, this,
		std::placeholders::_1, std::placeholders::_2));

	// Bind on moved callback
	UIEventTable.connectOnMovedEvent(std::bind(&UIWindow::movedCallback, this, 
		std::placeholders::_1, std::placeholders::_2));

	// Bind render callback
	getRenderable()->f_RenderOverride = std::bind(&UIWindow::renderCallback, this, 
		std::placeholders::_1, std::placeholders::_2);
}

void UIWindow::implUpdate()
{
}

void UIWindow::setSize(float x, float y)
{
	UIElement::setSize(x, y);
	reconfigureTitlebar();
	reconfigureWindow();
}

void UIWindow::setSize(const sf::Vector2f & point)
{
	UIElement::setSize(point);
	reconfigureTitlebar();
	reconfigureWindow();
}

void UIWindow::addChild(UIElement* child)
{
	// Add child element to the list of tracked element
	UIElement::addChild(child);

	bool isCoreElement = false;
	for (int32_t i = 0; i < 20; i++)
	{
		if (m_ComparativeIDs[i] == child->getName())
		{
			isCoreElement = true;
			break;
		}
	}

	if (!isCoreElement)
		m_TrackedElements.push_back(child);
}

void UIWindow::removeChild(UIElement* child)
{
	// Removed the tracked element if it can be found
	std::vector<UIElement*>::iterator it = m_TrackedElements.begin();
	for (; it != m_TrackedElements.end(); ++it)
	{
		if ((*it) == child)
		{
			m_TrackedElements.erase(it);
			break;
		}
	}
}

void UIWindow::setTitlebarText(std::string text)
{
	// Make sure titlebar exists and set text
	if (m_WindowFlags & WINDOW_FLAG_TITLE)
		m_WindowHeader.title->setText(text, sf::Color::White, 16U);
}

void UIWindow::setTitlebarColour(sf::Color colour)
{
	// Update the colour of each header element
	m_WindowHeader.top_left->getRenderable()->setColor(colour);
	m_WindowHeader.top_right->getRenderable()->setColor(colour);
	m_WindowHeader.btm_left->getRenderable()->setColor(colour);
	m_WindowHeader.btm_right->getRenderable()->setColor(colour);
	m_WindowHeader.top_middle->getRenderable()->setColor(colour);
	m_WindowHeader.btm_middle->getRenderable()->setColor(colour);
	m_WindowHeader.left->getRenderable()->setColor(colour);
	m_WindowHeader.right->getRenderable()->setColor(colour);
	m_WindowHeader.content->getRenderable()->setColor(colour);
}

void UIWindow::setWindowColour(sf::Color colour)
{
	// Update the colour of each window element
	m_Window.top_left->getRenderable()->setColor(colour);
	m_Window.top_right->getRenderable()->setColor(colour);
	m_Window.btm_left->getRenderable()->setColor(colour);
	m_Window.btm_right->getRenderable()->setColor(colour);
	m_Window.top_middle->getRenderable()->setColor(colour);
	m_Window.btm_middle->getRenderable()->setColor(colour);
	m_Window.left->getRenderable()->setColor(colour);
	m_Window.right->getRenderable()->setColor(colour);
	m_Window.container->getRenderable()->setColor(colour);
}

void UIWindow::releasedCallback(UIElement * element, sf::Mouse::Button button)
{
	// Make sure position is the same and we are inside titlebar
	if ((m_PositionPressedAbs - m_PositionPressed == m_PositionAbsolute) && m_AllowMovement)
		toggleElements();

	// Reset allow movement flag
	m_AllowMovement = false;
	m_AllowResize = false;
}

void UIWindow::pressedCallback(UIElement * element, sf::Mouse::Button button)
{
	// Make sure there is a titlebar before checking for intersection of mouse
	if (m_WindowFlags & WINDOW_FLAG_TITLE)
	{
		// Get sizes required for check
		float right_size = m_WindowHeader.right->getRenderable()->getDimensions().x;
		float bottom_size = m_WindowHeader.btm_middle->getRenderable()->getDimensions().y;

		// Do specialised check inside callback to make sure we are inside the titlebar
		bool check_left = (m_PositionPressedAbs.x > m_WindowHeader.left->getPositionAbsolute().x);
		bool check_top = (m_PositionPressedAbs.y > m_WindowHeader.top_middle->getPositionAbsolute().y);
		bool check_right = (m_PositionPressedAbs.x < m_WindowHeader.right->getPositionAbsolute().x + right_size);
		bool check_bottom = (m_PositionPressedAbs.y < m_WindowHeader.btm_middle->getPositionAbsolute().y + bottom_size);

		// Provided we are inside re-position the window
		if (check_left && check_top && check_right && check_bottom)
			m_AllowMovement = true;
	}

	if (m_WindowFlags & WINDOW_FLAG_RESIZE)
	{
		// Get sizes required for check
		sf::Vector2f btm_right_pos = m_Window.btm_right->getPositionAbsolute();
		sf::Vector2f btm_right_dim = m_Window.btm_right->getRenderable()->getDimensions();

		// Do specialised check inside callback to make sure we are inside the bottom right element
		bool check_left = (m_PositionPressedAbs.x > btm_right_pos.x - 10.0f);
		bool check_top = (m_PositionPressedAbs.y > btm_right_pos.y - 10.0f);
		bool check_right = (m_PositionPressedAbs.x < btm_right_pos.x + btm_right_dim.x);
		bool check_bottom = (m_PositionPressedAbs.y < btm_right_pos.y + btm_right_dim.y);

		// Provided we are inside re-size the window
		if (check_left && check_top && check_right && check_bottom)
			m_AllowResize = true;
	}
}

void UIWindow::movedCallback(UIElement * element, sf::Vector2f mouse_pos)
{
	// Make sure there is a titlebar and update pos
	if ((m_WindowFlags & WINDOW_FLAG_TITLE) && m_AllowMovement)
		setPosition(mouse_pos - m_PositionPressed);

	if ((m_WindowFlags & WINDOW_FLAG_RESIZE) && m_AllowResize)
	{
		sf::Vector2f new_size = mouse_pos - m_Position;

		if (!isZero(m_SizeMin))
		{
			new_size.x = std::max(new_size.x, m_SizeMin.x);
			new_size.y = std::max(new_size.y, m_SizeMin.y);
		}

		if (!isZero(m_SizeMax))
		{
			new_size.x = std::min(new_size.x, m_SizeMax.x);
			new_size.y = std::min(new_size.y, m_SizeMax.y);
		}

		setSize(new_size);
	}
}

void UIWindow::renderCallback(Renderable * renderable, sf::RenderTarget & target)
{
	/*sf::RectangleShape shape;
	shape.setPosition(getPositionAbsolute());
	shape.setSize(getSize());
	shape.setOutlineColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(1.0f);
	target.draw(shape);*/
}

void UIWindow::closeBtnReleasedCallback(UIElement * element, sf::Mouse::Button)
{
	hide();
}

void UIWindow::constructComparatives()
{
	// Create the comparative table to make sure that no integral elements of
	// the UIWindow get added to the tracked elements list
	m_ComparativeIDs[0]  = "_title";
	m_ComparativeIDs[1]  = "header_top_left";
	m_ComparativeIDs[2]  = "header_top_right";
	m_ComparativeIDs[3]  = "header_btm_left";
	m_ComparativeIDs[4]  = "header_btm_right";
	m_ComparativeIDs[5]  = "header_top_middle";
	m_ComparativeIDs[6]  = "header_btm_middle";
	m_ComparativeIDs[7]  = "header_left";
	m_ComparativeIDs[8]  = "header_right";
	m_ComparativeIDs[9]  = "header_content";
	m_ComparativeIDs[10] = "window_top_left";
	m_ComparativeIDs[11] = "window_top_right";
	m_ComparativeIDs[12] = "window_top_middle";
	m_ComparativeIDs[13] = "window_btm_left";
	m_ComparativeIDs[14] = "window_btm_right";
	m_ComparativeIDs[15] = "window_btm_middle";
	m_ComparativeIDs[16] = "window_left";
	m_ComparativeIDs[17] = "window_right";
	m_ComparativeIDs[18] = "window_container";
	m_ComparativeIDs[19] = "close_btn";
}

void UIWindow::constructTitlebar()
{
	// Check header bit flags
	if (m_WindowFlags & WINDOW_FLAG_TITLE)
	{
		// Instantiate the window header elements
		m_WindowHeader.top_left     = new UIElement(this, getID() + "header_top_left", sf::Vector2f(), "header_top_left");
		m_WindowHeader.top_right    = new UIElement(this, getID() + "header_top_right", sf::Vector2f(), "header_top_right");
		m_WindowHeader.btm_left	    = new UIElement(this, getID() + "header_btm_left", sf::Vector2f(), "header_btm_left");
		m_WindowHeader.btm_right    = new UIElement(this, getID() + "header_btm_right", sf::Vector2f(), "header_btm_right");
		m_WindowHeader.top_middle   = new UIElement(this, getID() + "header_top_middle", sf::Vector2f(), "header_top_middle");
		m_WindowHeader.btm_middle   = new UIElement(this, getID() + "header_btm_middle", sf::Vector2f(), "header_btm_middle");
		m_WindowHeader.left		    = new UIElement(this, getID() + "header_left", sf::Vector2f(), "header_left");
		m_WindowHeader.right	    = new UIElement(this, getID() + "header_right", sf::Vector2f(), "header_right");
		m_WindowHeader.content	    = new UIElement(this, getID() + "header_content", sf::Vector2f(), "header_content");

		// Register the header elements as UIElements in the UIManager
		m_ParentManager->addElement(m_WindowHeader.top_left);
		m_ParentManager->addElement(m_WindowHeader.top_right);
		m_ParentManager->addElement(m_WindowHeader.top_middle);
		m_ParentManager->addElement(m_WindowHeader.left);
		m_ParentManager->addElement(m_WindowHeader.right);
		m_ParentManager->addElement(m_WindowHeader.content);
		m_ParentManager->addElement(m_WindowHeader.btm_middle);
		m_ParentManager->addElement(m_WindowHeader.btm_left);
		m_ParentManager->addElement(m_WindowHeader.btm_right);
		
		// Give the header elements renderables
		m_WindowHeader.top_left->getRenderable()->pickElement("TitlebarTopLeft");
		m_WindowHeader.top_right->getRenderable()->pickElement("TitlebarTopRight");
		m_WindowHeader.btm_left->getRenderable()->pickElement("TitlebarBtmLeft");
		m_WindowHeader.btm_right->getRenderable()->pickElement("TitlebarBtmRight");
		m_WindowHeader.left->getRenderable()->pickElement("TitlebarLeft");
		m_WindowHeader.right->getRenderable()->pickElement("TitlebarRight");
		m_WindowHeader.top_middle->getRenderable()->pickElement("TitlebarTopMiddle");
		m_WindowHeader.btm_middle->getRenderable()->pickElement("TitlebarBtmMiddle");
		m_WindowHeader.content->getRenderable()->pickElement("TitlebarContent");

		m_WindowHeader.title = new UIStaticLabel(this, getID() + "_title", "_title");
		m_ParentManager->addElement(m_WindowHeader.title);
		m_WindowHeader.title->setText("My Window", sf::Color::White, 16.0f);

		if ((m_WindowFlags & WINDOW_FLAG_CLOSE) && !(m_WindowFlags & WINDOW_FLAG_NO_TITLE))
		{
			m_WindowHeader.close_button = new UIButton(this, getID() + "close_btn", sf::Vector2f(), "close_btn");
			m_WindowHeader.close_button->setDefaultElement("CloseButton");
			m_WindowHeader.close_button->setPressedElement("CloseButton");
			
			m_ParentManager->addElement(m_WindowHeader.close_button);
			m_WindowHeader.close_button->setSize(m_WindowHeader.close_button->getRenderable()->getDimensions());
			m_WindowHeader.close_button->setDrawHover(false);

			m_WindowHeader.close_button->UIEventTable.connectOnReleasedEvent(std::bind(
				&UIWindow::closeBtnReleasedCallback, this, std::placeholders::_1, std::placeholders::_2));
		}

		reconfigureTitlebar();
	}
}

void UIWindow::constructWindow()
{
	// Instantiate the window elements
	m_Window.top_left	= new UIElement(this, getID() + "window_top_left", sf::Vector2f(), "window_top_left");
	m_Window.top_right	= new UIElement(this, getID() + "window_top_right", sf::Vector2f(), "window_top_right");
	m_Window.top_middle = new UIElement(this, getID() + "window_top_middle", sf::Vector2f(), "window_top_middle");
	m_Window.btm_left	= new UIElement(this, getID() + "window_btm_left", sf::Vector2f(), "window_btm_left");
	m_Window.btm_right	= new UIElement(this, getID() + "window_btm_right", sf::Vector2f(), "window_btm_right");
	m_Window.btm_middle = new UIElement(this, getID() + "window_btm_middle", sf::Vector2f(), "window_btm_middle");
	m_Window.left		= new UIElement(this, getID() + "window_left", sf::Vector2f(), "window_left");
	m_Window.right		= new UIElement(this, getID() + "window_right", sf::Vector2f(), "window_right");
	m_Window.container	= new UIElement(this, getID() + "window_container", sf::Vector2f(), "window_container");

	// Register the window elements as UIElements in the UIManager
	m_ParentManager->addElement(m_Window.top_left);
	m_ParentManager->addElement(m_Window.top_right);
	m_ParentManager->addElement(m_Window.top_middle);
	m_ParentManager->addElement(m_Window.left);
	m_ParentManager->addElement(m_Window.right);
	m_ParentManager->addElement(m_Window.container);
	m_ParentManager->addElement(m_Window.btm_left);
	m_ParentManager->addElement(m_Window.btm_right);
	m_ParentManager->addElement(m_Window.btm_middle);

	// Give the window elements renderables
	m_Window.top_left->getRenderable()->pickElement("WindowTopLeft");
	m_Window.top_right->getRenderable()->pickElement("WindowTopRight");
	m_Window.top_middle->getRenderable()->pickElement("WindowTopMiddle");
	m_Window.left->getRenderable()->pickElement("WindowLeft");
	m_Window.right->getRenderable()->pickElement("WindowRight");
	m_Window.container->getRenderable()->pickElement("WindowContent");
	m_Window.btm_left->getRenderable()->pickElement("WindowBtmLeft");
	m_Window.btm_right->getRenderable()->pickElement("WindowBtmRight");
	m_Window.btm_middle->getRenderable()->pickElement("WindowBtmMiddle");

	reconfigureWindow();
}

void UIWindow::reconfigureTitlebar()
{
	if (m_WindowFlags & WINDOW_FLAG_TITLE)
	{
		// Calculate required sizes to position titlebar thusly
		sf::Vector2f content_size	   = m_WindowHeader.content->getRenderable()->getDimensions();
		sf::Vector2f left_corner_size  = m_WindowHeader.top_left->getRenderable()->getDimensions();
		sf::Vector2f right_corner_size = m_WindowHeader.top_right->getRenderable()->getDimensions();
		sf::Vector2f left_size		   = m_WindowHeader.left->getRenderable()->getDimensions();
		sf::Vector2f right_size		   = m_WindowHeader.right->getRenderable()->getDimensions();

		float calc_right = m_Size.x - right_corner_size.x;
		float calc_x = (m_Size.x - left_size.x - right_size.x) / content_size.x;
		float calc_y = 16.0f / content_size.y;

		// Apply positioning to each titlebar element
		m_WindowHeader.top_left->setPosition(sf::Vector2f(0.0f, 0.0f));
		m_WindowHeader.top_right->setPosition(sf::Vector2f(calc_right, 0.0f));
		m_WindowHeader.btm_left->setPosition(0.0f, left_corner_size.y + 16.0f);
		m_WindowHeader.btm_right->setPosition(calc_right, right_corner_size.y + 16.0f);
		m_WindowHeader.top_middle->setPosition(left_corner_size.x, 0.0f);
		m_WindowHeader.btm_middle->setPosition(left_corner_size.x, left_corner_size.y + 16.0f);
		m_WindowHeader.left->setPosition(0.0f, left_corner_size.y);
		m_WindowHeader.right->setPosition(m_Size.x - right_size.x, right_corner_size.y);
		m_WindowHeader.content->setPosition(left_size.x, left_size.y);

		// Scale content element size accordingly
		m_WindowHeader.content->getRenderable()->setScale(calc_x, calc_y);
		m_WindowHeader.top_middle->getRenderable()->setScale(calc_x, 1.0f);
		m_WindowHeader.btm_middle->getRenderable()->setScale(calc_x, 1.0f);
		m_WindowHeader.left->getRenderable()->setScale(1.0f, calc_y);
		m_WindowHeader.right->getRenderable()->setScale(1.0f, calc_y);

		float text_width = m_WindowHeader.title->getStaticText()->getGlobalBounds().width;
		m_WindowHeader.title->setPosition(sf::Vector2f((m_Size.x / 2.0f) - (text_width / 1.5f), 4.0f));
		m_RootPosition = 16.0f + left_size.y + m_WindowHeader.btm_left->getRenderable()->getDimensions().y;

		if ((m_WindowFlags & WINDOW_FLAG_CLOSE) && !(m_WindowFlags & WINDOW_FLAG_NO_TITLE))
			m_WindowHeader.close_button->setPosition(sf::Vector2f(m_Size.x - right_size.x - 18.0f, 6.0f));
	}
}

void UIWindow::reconfigureWindow()
{
	// Calculate required sizes to position
	sf::Vector2f content_size = m_Window.container->getRenderable()->getDimensions();
	sf::Vector2f left_corner_size = m_Window.top_left->getRenderable()->getDimensions();
	sf::Vector2f right_corner_size = m_Window.top_right->getRenderable()->getDimensions();
	sf::Vector2f left_size = m_Window.left->getRenderable()->getDimensions();
	sf::Vector2f right_size = m_Window.right->getRenderable()->getDimensions();
	sf::Vector2f root_as_vec = sf::Vector2f(0.0f, m_RootPosition);

	float calc_right = m_Size.x - right_corner_size.x;
	float calc_x = (m_Size.x - left_size.x - right_size.x) / content_size.x;
	float calc_y = (m_Size.y - m_RootPosition - left_size.y - right_size.y) / content_size.y;

	// Apply positioning to each element
	m_Window.top_left->setPosition(root_as_vec + sf::Vector2f(0.0f, 0.0f));
	m_Window.top_right->setPosition(root_as_vec + sf::Vector2f(calc_right, 0.0f));
	m_Window.btm_left->setPosition(sf::Vector2f(0.0f, m_Size.y - left_corner_size.y));
	m_Window.btm_right->setPosition(sf::Vector2f(calc_right, m_Size.y - left_corner_size.y));
	m_Window.top_middle->setPosition(root_as_vec + sf::Vector2f(left_corner_size.x, 0.0f));
	m_Window.btm_middle->setPosition(sf::Vector2f(left_corner_size.x, m_Size.y - left_corner_size.y));
	m_Window.left->setPosition(root_as_vec + sf::Vector2f(0.0f, left_corner_size.y));
	m_Window.right->setPosition(root_as_vec + sf::Vector2f(m_Size.x - right_size.x, right_corner_size.y));
	m_Window.container->setPosition(root_as_vec + sf::Vector2f(left_size.x, left_size.y));

	// Scale content element size accordingly
	m_Window.container->getRenderable()->setScale(calc_x, calc_y);
	m_Window.top_middle->getRenderable()->setScale(calc_x, 1.0f);
	m_Window.btm_middle->getRenderable()->setScale(calc_x, 1.0f);
	m_Window.left->getRenderable()->setScale(1.0f, calc_y);
	m_Window.right->getRenderable()->setScale(1.0f, calc_y);
}

void UIWindow::toggleElements()
{
	// Toggle the active of each core element
	m_Window.top_left->isActive()	? m_Window.top_left->hide()   : m_Window.top_left->show();
	m_Window.top_right->isActive()	? m_Window.top_right->hide()  : m_Window.top_right->show();
	m_Window.btm_left->isActive()	? m_Window.btm_left->hide()   : m_Window.btm_left->show();
	m_Window.btm_right->isActive()	? m_Window.btm_right->hide()  : m_Window.btm_right->show();
	m_Window.top_middle->isActive() ? m_Window.top_middle->hide() : m_Window.top_middle->show();
	m_Window.btm_middle->isActive() ? m_Window.btm_middle->hide() : m_Window.btm_middle->show();
	m_Window.left->isActive()		? m_Window.left->hide()		  : m_Window.left->show();
	m_Window.right->isActive()		? m_Window.right->hide()	  : m_Window.right->show();
	m_Window.container->isActive()	? m_Window.container->hide()  : m_Window.container->show();

	// Flip the active state of any tracked elements
	for (auto element : m_TrackedElements)
	{
		if (element->isActive())
			element->hide();
		else
			element->show();
	}
}
