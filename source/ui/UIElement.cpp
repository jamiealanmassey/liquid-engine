#include "UIElement.h"
#include "dynamic/UITooltip.h"
#include "../utilities/IDGenerator.h"
#include "../common/GameScene.h"

UIElement::UIElement() :
	m_Focused(false),
	m_AcceptsFocus(true),
	m_AcceptsFocusFromKbd(true),
	m_AcceptsEntered(true),
	m_DestroyNextFrame(false),
	m_RenderableExists(false),
	m_Enabled(true),
	m_Active(true),
	m_WaitHide(false),
	m_WaitDisable(false),
	m_WaitDestroy(false),
	m_TooltipFollow(true),
	m_CanLoseFocus(true),
	m_Position(sf::Vector2f()),
	m_PositionAbsolute(sf::Vector2f()),
	m_Size(sf::Vector2f()),
	m_SizeMin(sf::Vector2f()),
	m_SizeMax(sf::Vector2f()),
	m_TooltipOffset(sf::Vector2f(5.0f, 5.0f)),
	m_ID(""),
	m_Name(""),
	m_Renderable(nullptr),
	m_ParentElement(nullptr),
	m_ParentManager(nullptr),
	m_Tooltip(nullptr),
	m_CentreAnchor(eCentreAnchor::NONE)
{
}

UIElement::UIElement(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName) :
	m_Focused(false),
	m_AcceptsFocus(true),
	m_AcceptsFocusFromKbd(true),
	m_AcceptsEntered(true),
	m_DestroyNextFrame(false),
	m_RenderableExists(false),
	m_Enabled(true),
	m_Active(true),
	m_WaitHide(false),
	m_WaitDisable(false),
	m_WaitDestroy(false),
	m_TooltipFollow(true),
	m_Position(sf::Vector2f()),
	m_PositionAbsolute(sf::Vector2f()),
	m_Size(size),
	m_SizeMin(size),
	m_SizeMax(sf::Vector2f()),
	m_TooltipOffset(sf::Vector2f(5.0f, 5.0f)),
	m_ID(IDGenerator::Instance().getNextID(id)),
	m_Name(elementName),
	m_Renderable(nullptr),
	m_ParentElement(parent),
	m_ParentManager(nullptr),
	m_Tooltip(nullptr),
	m_CentreAnchor(eCentreAnchor::NONE)
{
	// If there is a parent given make sure this element is added as a child
	if (m_ParentElement)
		m_ParentElement->addChild(this);
}

UIElement::~UIElement()
{
}

void UIElement::initialise()
{
	// Instantiate the renderable
	std::string skin = m_ParentManager->getSkin();
	std::string data = m_ParentManager->getSkinData();
	
	// Setup the renderable
	m_Renderable = new UISkinRenderable(skin, data);
	m_Renderable->setOrigin(sf::Vector2f(0.0f, 0.0f));
	m_Renderable->setPosition(m_Position);
	m_Renderable->setCentreOrigin(false);
	m_Renderable->setRenderableType(Renderable::eRenderableType::UI);

	// Attempt to add it to the renderer
	if (m_ParentScene)
		m_ParentScene->getRenderer()->addRenderable(m_Renderable);

	// Call down to implemented initialise
	implInitialise();

	if (UITransitionTable.exists(UITRANSITION_CREATE))
		UITransitionTable.trigger(UITRANSITION_CREATE);
}

void UIElement::update()
{
	// Update any existing transition effects
	UITransitionTable.update();

	// Call to higher level implemented update
	implUpdate();

	if (m_WaitHide && UITransitionTable.isFinished(UITRANSITION_HIDE))
	{
		m_Active = false;
		m_WaitHide = false;
		m_Renderable->setActive(false);
		triggerListener(LISTEN_HIDE);
	}

	if (m_WaitDisable && UITransitionTable.isFinished(UITRANSITION_DISABLE))
	{
		m_Enabled = false;
		m_WaitDisable = false;
	}

	if (m_WaitDestroy && UITransitionTable.isFinishedAll())
	{
		m_DestroyNextFrame = true;
		m_WaitDestroy = false;
		triggerListener(LISTEN_DESTROY);
	}

	if (m_TooltipFollow && m_Tooltip && m_Active && m_Entered)
	{
		m_Tooltip->setPosition(sf::Vector2f(sf::Mouse::getPosition(
				*GameManager::instance().getRenderWindow())) + m_TooltipOffset);
	}
}

bool UIElement::acceptsFocus() const
{
	return m_AcceptsFocus;
}

bool UIElement::acceptsFocusFromKbd() const
{
	return m_AcceptsFocusFromKbd;
}

void UIElement::setPressed(bool flag)
{
	// Update the pressed flag
	m_Pressed = flag;

	if (m_Pressed)
		triggerListener(LISTEN_PRESSED);
	else
		triggerListener(LISTEN_RELEASED);
}

void UIElement::setEntered(bool flag)
{
	// Update the entered flag
	m_Entered = flag;

	if (m_Entered && m_Tooltip)
		m_Tooltip->show();
	else if (!m_Entered && m_Tooltip)
		m_Tooltip->hide();
}

void UIElement::addChild(UIElement* child)
{
	// Make sure element isn't already a child of this
	// element before adding
	for (auto element : m_Children)
	{
		if (child == element)
			return;
	}

	// Set the child's position and make sure this element
	// is the child's parent
	child->setParent(this);
	child->setPosition(child->getPosition());
	child->centre(child->m_CentreAnchor);

	// Resize this element and add child
	//fitElements(); // TODO
	m_Children.push_back(child);
}

void UIElement::removeChild(UIElement* child)
{
	// Find and remove the child
	ElementList::iterator itr = m_Children.begin();
	for (; itr != m_Children.end(); ++itr)
	{
		if (child == (*itr))
		{
			child->setParent(nullptr);
			child->setPosition(child->getPosition());
			m_Children.erase(itr);
			break;
		}
	}

	// Resize this element
	fitElements();
}

void UIElement::listen(UIElement* element, int32_t eventID)
{
	if (m_Listeners.find(eventID) != m_Listeners.end())
	{
		for (auto compare : m_Listeners[eventID])
		{
			if (compare == element)
				return;
		}
	}

	m_Listeners[eventID].push_back(element);
}

void UIElement::ignore(UIElement* element, int32_t eventID)
{
	if (m_Listeners.find(eventID) == m_Listeners.end())
		return;

	ElementList::iterator itr = m_Listeners[eventID].begin();
	for (; itr != m_Listeners[eventID].end(); ++itr)
	{
		if ((*itr) == element)
		{
			itr = m_Listeners[eventID].erase(itr);

			if (itr == m_Listeners[eventID].end())
				break;
		}
	}
}

void UIElement::triggerListener(int32_t eventID)
{
	if (!m_Listeners[eventID].empty())
	{
		for (auto listener : m_Listeners[eventID])
			listener->acceptListener(this, eventID);
	}
}

void UIElement::acceptListener(UIElement* element, int32_t eventID)
{
}

const UIElement::ElementList& UIElement::getChildrenConst() const
{
	return m_Children;
}

UIElement::ElementList& UIElement::getChildren()
{
	return m_Children;
}

UIElement* UIElement::findChildByID(std::string id)
{
	// Search all children in the ElementList for an
	// element that matches this id
	for (auto element : m_Children)
	{
		if (element->getID() == id)
			return element;
	}

	// No element by that id was found
	return nullptr;
}

UIElement* UIElement::findChildByName(std::string elementName)
{
	// Search all children in the ElementList for an
	// element that matches this name
	for (auto element : m_Children)
	{
		if (element->getName() == elementName)
			return element;
	}

	// No element by that name was found
	return nullptr;
}

void UIElement::destroyChildren()
{
	// Destroy all child elements
	for (auto element : m_Children)
		element->destroy();

	// Clear the child element list
	m_Children.clear();
}

UIElement* UIElement::getParent() const
{
	return m_ParentElement;
}

UIElement* UIElement::getNextSibling() const
{
	// First make sure the parent exists
	if (m_ParentElement == nullptr)
		return nullptr;

	// Store the parent children and create a variable to store
	// our element position
	ElementList& elements = m_ParentElement->getChildren();
	int32_t elementPos = -1;

	// Find and assign the element position
	for (int32_t i = 0; i < elements.size(); i++)
	{
		if (elements[i] == this)
			elementPos = i;
	}

	// In the unlikely event the element was not found or the next sibling
	// element doesn't exist return null otherwise return the next sibling
	// of this element
	if ((elementPos == -1) || ((elementPos + 1) > elements.size()))
		return nullptr;
	else
		return elements[elementPos + 1];
}

UIElement* UIElement::getPreviousSibling() const
{
	// First make sure the parent exists
	if (m_ParentElement == nullptr)
		return nullptr;

	// Store the parent children and create a variable to store
	// our element position
	ElementList& elements = m_ParentElement->getChildren();
	int32_t elementPos = -1;

	// Find and assign the element position
	for (int32_t i = 0; i < elements.size(); i++)
	{
		if (elements[i] == this)
			elementPos = i;
	}

	// In the unlikely event the element was not found or the previous sibling
	// element doesn't exist return null otherwise return the previous sibling
	// of this element
	if ((elementPos == -1) || ((elementPos - 1) <= 0))
		return nullptr;
	else
		return elements[elementPos - 1];
}

void UIElement::setMinSize(const sf::Vector2f& size)
{
	// Assign the new minimum size
	m_SizeMin = size;

	// Update sizes
	setSize(getSize());
}

void UIElement::setMaxSize(const sf::Vector2f& size)
{
	// Assign the new maximum size
	m_SizeMax = size;

	// Update sizes
	setSize(getSize());
}

void UIElement::setSize(float width, float height)
{
	// Assign the new size
	sf::Vector2f size;
	size.x = width;
	size.y = height;

	// Find out if there is a min or max size, and if so, enforce
	// min/max appropriately
	if (m_SizeMin.x != 0.0f && m_SizeMin.y != 0.0f)
	{
		size.x = std::max(size.x, m_SizeMin.x);
		size.y = std::max(size.y, m_SizeMin.y);
	}

	if (m_SizeMax.x != 0.0f && m_SizeMax.y != 0.0f)
	{
		size.x = std::min(size.x, m_SizeMax.x);
		size.y = std::min(size.y, m_SizeMax.y);
	}

	// Assign the new size
	m_Size = size;

	// Call to resize
	UIEventTable.callOnResize(this, m_Size);
}

void UIElement::setSize(const sf::Vector2f& size)
{
	// Assign the new size
	setSize(size.x, size.y);
}

sf::Vector2f UIElement::getPositionAbsolute() const
{
	return m_PositionAbsolute;
}

sf::Vector2f UIElement::getPosition() const
{
	return m_Position;
}

sf::IntRect UIElement::getBounds() const
{
	// Find and return the bounds of this element
	sf::IntRect bounds;
	bounds.left   = getPosition().x;
	bounds.top    = getPosition().y;
	bounds.width  = getSize().x;
	bounds.height = getSize().y;
	return bounds;
}

void UIElement::parentMoved()
{
	setPosition(getPosition());
}

void UIElement::fitElements()
{
	// First make sure there are children for the calculation
	if (m_Children.empty())
		return;

	// Create some variables to store and sample each position of the four
	// points of the element that make up its bounds
	float minimumLeft   = getPosition().x;
	float minimumTop    = getPosition().y;
	float maximumRight  = minimumLeft + getSize().x;
	float maximumBottom = minimumTop + getSize().y;

	// Iterate each child element, if it's position is further than
	// the current bounds of the element update variables
	for (auto element : m_Children)
	{
		// Store this elements position and size
		sf::Vector2f elementPos = element->getPosition();
		sf::Vector2f elementSize = element->getSize();

		// Use min/max to store new bounds
		minimumLeft   = std::min(minimumLeft, elementPos.x);
		minimumTop    = std::min(minimumTop, elementPos.y);
		maximumRight  = std::max(maximumRight, (elementPos.x + elementSize.x));
		maximumBottom = std::max(maximumBottom, (elementPos.y + elementSize.y));
	}

	// Update the element with it's new position and bounds
	setPosition(sf::Vector2f(minimumLeft, minimumTop));
	setSize(sf::Vector2f(maximumRight, maximumBottom));
}

void UIElement::centre(UIElement::eCentreAnchor anchor)
{
	// Check to see which axis we want to centre with
	bool alignHorizontal = (anchor == eCentreAnchor::HORIZONTAL || anchor == eCentreAnchor::BOTH);
	bool alignVertical = (anchor == eCentreAnchor::VERTICAL || anchor == eCentreAnchor::BOTH);

	// Store the changing dimensions, the position and size
	sf::Vector2f sizeDims = sf::Vector2f();
	sf::Vector2f position = getPosition();
	sf::Vector2f size	  = getSize();

	//GameScene* parentScene = m_ParentManager->getParentScene();

	// Check if we need to align the element horizontally
	if (alignHorizontal)
	{
		// Find out if the element has a parent
		// true: Centre the element in relation to its parent
		// false: Centre the element in relation to the window
		if (m_ParentElement)
			sizeDims.x = m_ParentElement->getSize().x;
		else
			sizeDims.x = 0.0f; //parentScene->getUIWindow().getSize().x;
						
		// Assign the new horizontal position
		position.x = (sizeDims.x / 2.0f) - (size.x / 2.0f);
	}

	// Check if we need to align the element vertically
	if (alignVertical)
	{
		// Find out if the element has a parent
		// true: Centre the element in relation to its parent
		// false: Centre the element in relation to the window
		if (m_ParentElement)
			sizeDims.y = m_ParentElement->getSize().y;
		else
			sizeDims.y = 0.0f; //parentScene->getUIWindow().getSize().y;

		// Assign the new vertical position
		position.y = (sizeDims.y / 2.0f) - (size.y / 2.0f);
	}

	// Pass the new position to the element
	setPosition(position);
}

void UIElement::move(float x, float y)
{
	// Add the given coordinates to the current element
	// position
	sf::Vector2f position = getPosition();
	position.x += x;
	position.y += y;

	// Set the new position
	setPosition(position);
}

void UIElement::move(const sf::Vector2f& point)
{
	// Call down to second move implementation
	move(point.x, point.y);
}

void UIElement::setPosition(const sf::Vector2f& point)
{
	// Set the new position
	m_Position.x = point.x;
	m_Position.y = point.y;

	// Find out wether the element has a parent, if it does position it in relation 
	// to the parent, otherwise assign the absolute position to the actual position
	if (m_ParentElement)
	{
		m_PositionAbsolute.x = m_ParentElement->getPositionAbsolute().x + m_Position.x;
		m_PositionAbsolute.y = m_ParentElement->getPositionAbsolute().y + m_Position.y;
	}
	else
	{
		m_PositionAbsolute.x = m_Position.x;
		m_PositionAbsolute.y = m_Position.y;
	}

	if (m_Renderable)
		m_Renderable->setPosition(m_PositionAbsolute);

	// (re-)position child elements
	for (auto element : m_Children)
		element->parentMoved();

	if (!m_TooltipFollow && m_Tooltip)
		m_Tooltip->setPosition(m_PositionAbsolute + (m_Size / 2.0f) + m_TooltipOffset);
}

void UIElement::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

void UIElement::lowerZ()
{
	//m_ParentManager->shuffleElementZ(0);
}

void UIElement::raiseZ()
{
	//int32_t count = m_ParentManager->getElements().size();
	//m_ParentManager->shuffleElementZ(count);
}

void UIElement::show()
{
	for (auto child : m_Children)
		child->show();

	// Make sure the element is not already showing
	if (!m_Active)
	{
		// Activate the renderable and make sure it is enabled
		m_Active = true;
		m_Renderable->setActive(true);

		// Call the transition effect if it exists
		if (UITransitionTable.exists(UITRANSITION_SHOW))
			UITransitionTable.trigger(UITRANSITION_SHOW);

		// Call to listeners
		triggerListener(LISTEN_SHOW);
	}
}

void UIElement::hide()
{
	// Make sure the element is already showing
	if (m_Active)
	{
		// If the renderable exists activate it
		if (m_RenderableExists)
			m_Renderable->setActive(false);

		// Call the transition effect if it exists
		if (UITransitionTable.exists(UITRANSITION_HIDE))
		{
			UITransitionTable.trigger(UITRANSITION_HIDE);
			triggerListener(LISTEN_HIDE);
			m_WaitHide = true;
		}
		else
		{
			m_Active = false;
			m_Renderable->setActive(false);
		}
	}

	for (auto child : m_Children)
		child->hide();
}

void UIElement::enable()
{
	// Make sure the element is already not enabled
	if (!m_Enabled)
	{
		m_Enabled = true;
		
		if (UITransitionTable.exists(UITRANSITION_ENABLE))
			UITransitionTable.trigger(UITRANSITION_ENABLE);
	}

	for (auto child : m_Children)
		child->enable();
}

void UIElement::disable()
{
	// Make sure the element is already enabled
	if (m_Enabled)
	{
		if (UITransitionTable.exists(UITRANSITION_DISABLE))
		{
			UITransitionTable.trigger(UITRANSITION_DISABLE);
			m_WaitDisable = true;
		}
		else
			m_Enabled = false;
	}

	for (auto child : m_Children)
		child->disable();
}

/*void UIElement::attachTooltip(UITooltipCtrl* tooltip)
{
	// TODO: Pass tooltip
}*/

void UIElement::attachTooltip(std::string info, std::string font)
{
	m_Tooltip = new UITooltip(this, getID() + "_tooltip", sf::Vector2f(), "_tooltip");
	m_ParentManager->addElement(m_Tooltip);
	m_Tooltip->getRenderableText()->setFont(font);
	m_Tooltip->setPosition(getPositionAbsolute() + (getSize() / 2.0f) + m_TooltipOffset);
	m_Tooltip->setTooltipText(info);
	m_Tooltip->hide();
}

bool UIElement::removeTooltip()
{
	// If the tooltip exists remove it as a child and
	// destroy it from the manager
	/*if (m_Tooltip)
	{
		removeChild(m_Tooltip);
		m_Tooltip->destroy();
		return true;
	}*/

	// Return false as tooltip doesn't exist
	return false;
}

UITooltip* UIElement::getTooltip()
{
	return m_Tooltip;
}

std::string UIElement::getTooltipText() const
{
	// TODO: return tooltip text
	/*if (m_Tooltip)*/

	return "";
}

std::string UIElement::getID() const
{
	// Get the element ID
	return m_ID;
}

std::string UIElement::getName() const
{
	// Get the element name
	return m_Name;
}

void UIElement::setID(std::string id)
{
	// Give the element a new ID
	m_ID = IDGenerator::Instance().getNextID(id);
}

void UIElement::setName(std::string name)
{
	// Give the element a new name
	m_Name = name;
}

void UIElement::close()
{
	disable();
	hide();
}

void UIElement::destroy()
{
	if (UITransitionTable.exists(UITRANSITION_DESTROY))
	{
		UITransitionTable.trigger(UITRANSITION_DESTROY);
		triggerListener(LISTEN_DESTROY);
		m_WaitDestroy = true;
	}
	else
		m_DestroyNextFrame = true;
}

void UIElement::setCanFocus(bool flag)
{
	m_AcceptsFocus = flag;
}

void UIElement::setCanFocusFromKbd(bool flag)
{
	m_AcceptsFocusFromKbd = flag;
}

void UIElement::setCanEnter(bool flag)
{
	m_AcceptsEntered = flag;
}

void UIElement::setFocus(bool flag)
{
	// Update the focused flag for this element
	if (m_AcceptsFocus || m_AcceptsFocusFromKbd)
		m_Focused = flag;
}

void UIElement::setTooltipFollow(bool flag)
{
	m_TooltipFollow = flag;
}

void UIElement::setTooltipOffset(const sf::Vector2f& point)
{
	m_TooltipOffset = point;

	if (!m_TooltipFollow && m_Tooltip)
		m_Tooltip->setPosition(getPositionAbsolute() + (getSize() / 2.0f) + m_TooltipOffset);
}

bool UIElement::canAcceptFocus() const
{
	return m_AcceptsFocus;
}

bool UIElement::canAcceptFocusFromKbd() const
{
	return m_AcceptsFocusFromKbd;
}

bool UIElement::canEnter() const
{
	return m_AcceptsEntered;
}

bool UIElement::hasFocus() const
{
	return m_Focused;
}

bool UIElement::canLoseFocus() const
{
	return m_CanLoseFocus;
}

bool UIElement::isInside(float x, float y) const
{
	// Sample each bound against every point and store result
	bool checkLeft   = (x > m_PositionAbsolute.x);
	bool checkTop    = (y > m_PositionAbsolute.y);
	bool checkRight  = (x < (m_PositionAbsolute.x + m_Size.x));
	bool checkBottom = (y < (m_PositionAbsolute.y + m_Size.y));

	// Give back the calculated result
	return (checkLeft && checkTop && checkRight && checkBottom);
}

bool UIElement::isInside(const sf::Vector2f & point) const
{
	// Call down to isInside(x, y)
	return isInside(point.x, point.y);
}
