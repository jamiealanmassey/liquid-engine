#include "Entity.h"
#include "GameScene.h"
#include "GameManager.h"
#include "../utilities/DeltaTime.h"

Entity::Entity(sf::Vector2f position, std::string uid) :
	m_Moved(false),
	m_RenderableExists(false),
	m_Physics(false),
	m_EntityType(ENTITY_TYPE_UNKNOWN),
	m_ParentScene(nullptr),
	m_Renderable(nullptr),
	m_EntityState(eEntityState::ENTITYSTATE_ALIVE),
	m_Parent(nullptr),
	m_Box2DBody(nullptr),

	f_SetPosition(nullptr),
	f_AddPosition(nullptr),
	f_Update(nullptr),
	f_UpdatePost(nullptr),
	f_Killed(nullptr),

	f_OnKeyPressed(nullptr),
	f_OnKeyReleased(nullptr),
	f_OnMousePressed(nullptr),
	f_OnMouseReleased(nullptr),

	f_OnCollisionBegin(nullptr),
	f_OnCollisionEnd(nullptr),
	f_OnBodyCollisionBegin(nullptr),
	f_OnBodyCollisionEnd(nullptr)
{
	m_Position = position;
	m_UID	   = uid;
}

Entity::~Entity()
{
	// If renderable exists make sure to remove the renderable from
	// the renderer pipeline
	if (m_Renderable)
		m_ParentScene->getRenderer()->removeRenderable(m_Renderable);

	// Destroy for Box2D
	destroyBox2D();

	// If the Entity has a parent remove this Entity as a child
	// from its list of children
	if (m_Parent)
		m_Parent->removeChild(this);

	// Function callback for when the Entity is destroyed
	if (f_Killed)
		f_Killed(this);
}

void Entity::update()
{
	// Reset flag for Entity movement
	m_Moved = false;

	// Make sure the Entity is alive
	if (m_EntityState != eEntityState::ENTITYSTATE_ALIVE)
		return;

	// If the Entity has a body make sure to update the position
	// with the position of the Box2D body
	if (m_Box2DBody)
	{
		sf::Vector2f pos;
		pos.x = (m_Box2DBody->GetPosition().x * 50.0f);
		pos.y = (m_Box2DBody->GetPosition().y * 50.0f);
		setPosition(pos);
	}

	// Function callback for when the Entity is updated
	if (f_Update)
		f_Update(this, Delta);

	// Call down to inherited update
	implUpdate();

	// For all active tween functions update and call corresponding function
	for (auto tween : m_Tweening)
	{
		// Add elapsed time and call func
		tween.elapsed += Delta;
		tween.func_ptr(tween.elapsed);

		// If elapsed time has passed timer, tweening is done
		if (tween.elapsed >= tween.timer)
			tween.finished = true;
	}

	// Update tweeners
	updateTween();

	// Iterate over each active tweening mechanism and if it has finished erase it from
	// the list of running tweeners and reset iterator position
	std::vector<TweenData>::iterator tween_it = m_Tweening.begin();
	for (; tween_it != m_Tweening.end(); ++tween_it)
	{
		if ((*tween_it).finished)
			tween_it = m_Tweening.erase(tween_it);
	}
}

void Entity::updatePost()
{
	// Function callback for Entity postUpdate()
	if (f_UpdatePost)
		f_UpdatePost(this, Delta);

	// Call down to inherited updatePost
	implUpdatePost();
}

void Entity::updateTween()
{
	// Iterate through each active tweener calling to the function pointer
	// with the passed time; also check for tweener's that have finished
	for (auto tween : m_Tweening)
	{
		// Add to elapsed time and call down to stored function
		tween.elapsed = std::min(tween.elapsed + Delta, tween.timer);
		tween.func_ptr(Delta);

		// If the elapsed time has surpassed the timer set finished flag to true
		if (tween.elapsed >= tween.timer)
			tween.finished = true;
	}
}

void Entity::attachRenderable(Renderable* renderable, bool centre)
{
	// Assign new renderable and give position
	m_RenderableExists = true;
	m_Renderable = renderable;
	m_Renderable->setPosition(m_Position);
	m_Renderable->setRenderableType(Renderable::eRenderableType::WORLD);
	m_Renderable->setCentreOrigin(centre);

	if (m_Renderable->checkCentred())
		m_Renderable->setOrigin(m_Renderable->getDimensions() / 2.0f);

	// Make sure renderable exists in GameScene
	if (m_ParentScene)
		m_ParentScene->getRenderer()->addRenderable(renderable);
}

void Entity::attachTweener(TweenData data)
{
	// Before attaching a tweener to the Entity we need to make sure there 
	// is a function pointer to be called
	if (data.func_ptr == nullptr)
	{
		// TODO: Output console error
		return;
	}

	// Push back new tweening data
	m_Tweening.push_back(data);
}

void Entity::setPosition(sf::Vector2f pos)
{
	// Update moved flag
	m_Moved = true;

	// Assign new position of the entity
	m_Position.x = pos.x;
	m_Position.y = pos.y;

	// Update renderable position if we have one
	if (m_RenderableExists)
		m_Renderable->setPosition(m_Position);

	// Iterate through children and assign new position accordingly
	for (auto child : m_Children)
		child->setPosition(m_Position /*- (child->getPosition() + m_Position)*/);

	// Function callback for setPosition(x, y)
	if (f_SetPosition)
		f_SetPosition(this, m_Position.x, m_Position.y);

	// Update bounding body
	if (m_Box2DBody)
	{
		sf::Vector2f new_pos;
		new_pos.x = m_Position.x * 0.02f;
		new_pos.y = m_Position.y * 0.02f;
		m_Box2DBody->SetTransform(b2Vec2(new_pos.x, new_pos.y), 0.0f);
	}
}

void Entity::setPosition(float x, float y)
{
	// Call down to setPosition(Vector2f)
	setPosition(sf::Vector2f(x, y));
}

void Entity::addPosition(sf::Vector2f pos)
{
	// Update moved flag
	m_Moved = true;

	// Assign new position of the entity
	m_Position.x += pos.x;
	m_Position.y += pos.y;

	// Update renderable position if we have one
	if (m_RenderableExists)
		m_Renderable->setPosition(m_Position);

	// Iterate through children and assign new position accordingly
	for (auto child : m_Children)
		child->setPosition(m_Position /*- (child->getPosition() + m_Position)*/);

	// Function callback for setPosition(x, y)
	if (f_AddPosition)
		f_AddPosition(this, m_Position.x, m_Position.y);

	// Update bounding body
	if (m_Box2DBody)
	{
		sf::Vector2f new_pos;
		new_pos.x = m_Position.x * 0.02f;
		new_pos.y = m_Position.y * 0.02f;
		m_Box2DBody->SetTransform(b2Vec2(new_pos.x, new_pos.y), 0.0f);
	}
}

void Entity::addPosition(float x, float y)
{
	// Call down to addPosition(Vector2f)
	addPosition(sf::Vector2f(x, y));
}

void Entity::setParent(Entity* parent)
{
	// If the child already has a parent remove it from that parents list
	if (m_Parent)
		m_Parent->removeChild(this);

	// Assign new parent
	m_Parent = parent;
}

void Entity::addChild(Entity* child)
{
	// Add child to list of children, assign this Entity as the parent to that child
	// and finally adjust the position
	m_Children.push_back(child);
	child->setPosition(child->getPosition() + m_Position);
	child->setParent(this);
}

void Entity::removeChild(Entity* child)
{
	// Setup a vector iterator and iterate through each child until we find a match,
	// once we do remove that child from the vector and exit the function
	std::vector<Entity*>::iterator child_it = m_Children.begin();
	for (; child_it != m_Children.end(); ++child_it)
	{
		if ((*child_it) == child)
		{
			m_Children.erase(child_it);
			break;
		}
	}
}

void Entity::constructBox2D(b2BodyDef definition)
{
	// Create Body from definition
	m_Box2DBodyDef = definition;
	m_Box2DBody = m_ParentScene->getBox2DWorld()->CreateBody(&m_Box2DBodyDef);
	m_Box2DBody->SetUserData(this);

	// Update position
	setPosition(definition.position.x * 50.0f, definition.position.y * 50.0f);
}

void Entity::constructBox2DFixture(b2FixtureDef fixture)
{
	// If the Box2D body exists create fixture passing the Entity as data
	if (m_Box2DBody)
	{
		fixture.userData = this;
		m_Box2DBody->CreateFixture(&fixture);
	}
}

void Entity::destroyBox2D()
{
	// If there is a body, destroy it
	if (m_Box2DBody)
	{
		m_ParentScene->getBox2DWorld()->DestroyBody(m_Box2DBody);
		m_Box2DBody = nullptr;
	}
}

bool Entity::isPointInside(const sf::Vector2f& v, bool use_initial)
{
	if (m_RenderableExists)
	{
		sf::Vector2f dims;

		if(use_initial)
		{
			dims.x = m_Renderable->getDimensionsInit().x / 2.0f;
			dims.y = m_Renderable->getDimensionsInit().y / 2.0f;
		}
		else
		{
			dims.x = m_Renderable->getDimensions().x / 2.0f;
			dims.y = m_Renderable->getDimensions().y / 2.0f;
		}

		if (v.x > m_Position.x - dims.x &&
			v.x < m_Position.x + dims.x &&
			v.y > m_Position.y - dims.y &&
			v.y < m_Position.y + dims.y)
		{
			return true;
		}
	}

	return false;
}
