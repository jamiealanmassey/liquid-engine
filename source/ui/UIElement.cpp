#include "UIElement.h"
#include "../common/GameScene.h"

UIElement::UIElement(sf::Vector2f position, std::string id) :
	m_Entered(false),
	m_Focused(false),
	m_Pressed(false),
	m_AllowInteraction(true),
	m_RenderableExists(false),
	m_DestroyNextFrame(false),
	m_Anchor(eAnchor::ANCHOR_NONE),
	m_Renderable(nullptr),
	m_ParentScene(nullptr),
	m_Parent(nullptr)
{
	m_Position		  = position;
	m_UID			  = id;
	m_TransitionState = new UITransitionState(this);
}

UIElement::~UIElement()
{
	// If renderable exists remove from the scene and destroy it
	if (m_Renderable)
	{
		m_ParentScene->getRenderer()->removeRenderable(m_Renderable);
		delete m_Renderable;
	}

	// Detach children
	for (auto child : m_Children)
		child->setParent(nullptr);

	// Clear children container
	m_Children.clear();
}

void UIElement::setPosition(sf::Vector2f position)
{
	// Assign new position of the entity
	m_Position.x = position.x;
	m_Position.y = position.y;

	// Update renderable position if we have one
	if (m_RenderableExists)
		m_Renderable->setPosition(m_Position);

	// Iterate through children and assign new position accordingly
	for (auto child : m_Children)
		child->setPosition(child->getPositionRelative() + m_Position);
}

void UIElement::setPosition(float x, float y)
{
	// Call down to setPosition(Vector2f)
	setPosition(sf::Vector2f(x, y));
}

void UIElement::setPositionRelative(sf::Vector2f position)
{
	// Assign new relative position of the entity
	m_PositionRelative.x = position.x;
	m_PositionRelative.y = position.y;
}

void UIElement::setPositionRelative(float x, float y)
{
	// Call down to setPosition(Vector2f)
	setPositionRelative(sf::Vector2f(x, y));
}

void UIElement::alignElement()
{
	// TODO
}

void UIElement::attachRenderable(Renderable* renderable)
{
	// Assign new renderable and give position
	m_RenderableExists = true;
	m_Renderable	   = renderable;

	m_Renderable->setOrigin(sf::Vector2f(0.0f, 0.0f));
	m_Renderable->setPosition(m_Position);
	m_Renderable->setCentreOrigin(false);
	m_Renderable->setRenderableType(Renderable::eRenderableType::UI);

	// Make sure renderable exists in GameScene
	if (m_ParentScene)
		m_ParentScene->getRenderer()->addRenderable(renderable);
}

void UIElement::addChild(UIElement * child)
{
	// Make sure child doesn't already exist
	for(auto c : m_Children)
	{
		if (c == child)
			return;
	}

	// Update parent and push back to vector
	child->setParent(this);
	child->setPosition(getPosition() + child->getPositionRelative());
	child->alignElement();
	m_Children.push_back(child);
}

void UIElement::addChild(std::vector<UIElement*> children)
{
	// Iterate over given elements and call down to addChild()
	for (auto c : children)
		addChild(c);
}

void UIElement::removeChild(UIElement * child)
{
	// Iterate over elements and find corresponding child, once found use
	// the iterator position to remove it
	std::vector<UIElement*>::iterator it = m_Children.begin();
	for (; it != m_Children.end(); ++it)
	{
		if (child == (*it))
		{
			m_Children.erase(it);
			break;
		}
	}
}
