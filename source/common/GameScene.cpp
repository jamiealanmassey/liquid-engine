#include "GameScene.h"
#include "GameManager.h"
#include "../utilities/Vectors.h"
#include "../utilities/DeltaTime.h"

GameScene::GameScene(LuaInstance* lua_instance, std::string state_name) :
	m_GameManager(nullptr),
	m_AllowUpdate(true),
	m_AllowUpdateEvents(true),
	m_AllowRender(true),
	m_AllowPostProcesses(true)
{
	// Seed time
	std::srand(std::time(nullptr));

	// Setup variables for use
	m_LuaInstance = lua_instance;
	m_StateName   = state_name;

	// If we have an LuaInstance we want to initialise() it and make sure that
	// all relevant functions are registered
	if (m_LuaInstance)
	{
		m_LuaInstance->init();
		m_LuaInstance->registerLuaFunctions();
	}
}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	// Create renderer, Box2D world, UIManager and contact listener
	m_Renderer		  = new Renderer(this);
	m_UIManager		  = new UIManager(this);
	m_Box2DWorld	  = new b2World(b2Vec2(0.0f, 0.0f));
	m_ContactListener = new ContactListener();

	// Connect contact listener to world
	m_Box2DWorld->SetContactListener(m_ContactListener);

	// Call down to override
	implInitialise();
}

void GameScene::updateEvents(EventData event_data)
{
	if (!m_AllowUpdateEvents)
		return;

	for (auto entity : m_Entities)
	{
		if (event_data.key_pressed)
		{
			if (entity->f_OnKeyPressed)
				entity->f_OnKeyPressed(event_data.data_key_pressed);
		}
		else if (event_data.key_released)
		{
			if (entity->f_OnKeyReleased)
				entity->f_OnKeyReleased(event_data.data_key_released);
		}
		else if (event_data.mouse_button_pressed)
		{
			if (entity->f_OnMousePressed)
				entity->f_OnMousePressed(event_data.data_mouse_pos, event_data.data_mouse_pressed);
		}
		else if (event_data.mouse_button_released)
		{
			if (entity->f_OnMouseReleased)
				entity->f_OnMouseReleased(event_data.data_mouse_pos, event_data.data_mouse_released);
		}
	}
}

void GameScene::update(float delta)
{
	if (!m_AllowUpdate)
		return;

	// Call down to the renderer
	m_Renderer->update();

	// Update Box2D World
	if (m_Box2DWorld)
		m_Box2DWorld->Step(Delta, 6, 2);

	// Update all entities
	for (auto entity : m_Entities)
		entity->update(delta);

	// Update all entities for post
	for (auto entity : m_Entities)
		entity->updatePost(delta);

	// Update UIManager
	m_UIManager->update(delta, m_GameManager->getEventData());

	// Iterate through entities and remove any dead ones
	std::vector<Entity*>::iterator it = m_Entities.begin();
	for (; it != m_Entities.end(); ++it)
	{
		if ((*it)->getEntityState() == Entity::eEntityState::ENTITYSTATE_DEAD)
		{
			((*it))->implKill();
			it = m_Entities.erase(it);

			if (it == m_Entities.end())
				break;
		}
	}
	
	// Call down to user override
	implUpdate();
}

void GameScene::render(sf::RenderTarget& target)
{
	// Call down to the Renderer
	m_Renderer->render(target);
}

void GameScene::addEntity(Entity* entity)
{
	// Add entity to the Scene
	m_Entities.push_back(entity);
	entity->setGameScene(this);
	entity->implInitialise();

	// If the Entity has a renderable add it to the Renderer
	if (entity->checkRenderable())
		m_Renderer->addRenderable(entity->getRenderable());
}

void GameScene::addEntity(std::vector<Entity*> entities)
{
	// Iterate over each passed entity and call down to addEntity(entity)
	for (auto entity : entities)
		addEntity(entity);
}

Entity* GameScene::getEntityAtPoint(sf::Vector2f point)
{
	// Iterate through each Entity in the scene so we can check points
	for (uint32_t i = 0; i < m_Entities.size(); i++)
	{
		// If it is renderable we need to take into account the texture size of the renderable as well
		// as the position of the entity, otherwise we can straight up make a position comparison
		if (m_Entities[i]->checkRenderable())
		{
			// Take a pointer to the renderable
			Renderable* renderable_ptr = m_Entities[i]->getRenderable();

			// If the point is inside of the renderable and the Entity then return this Entity
			if (point.x > (m_Entities[i]->getPosition().x - renderable_ptr->getTexture()->getSize().y) &&
				point.y > (m_Entities[i]->getPosition().y - renderable_ptr->getTexture()->getSize().y) &&
				point.x < (m_Entities[i]->getPosition().x + renderable_ptr->getTexture()->getSize().x) &&
				point.y < (m_Entities[i]->getPosition().y + renderable_ptr->getTexture()->getSize().y))
			{
				return m_Entities[i];
			}
		}
		else
		{
			// If the point is equal to the position of the Entity return it
			if (point == m_Entities[i]->getPosition())
				return m_Entities[i];
		}
	}

	// Otherwise we have no Entity at this position
	return nullptr;
}

Entity* GameScene::getEntityAtPointWithUID(sf::Vector2f point, std::string uid)
{
	// Iterate through each Entity in the scene so we can check points
	for (uint32_t i = 0; i < m_Entities.size(); i++)
	{
		// First make sure that the UID matches
		if (m_Entities[i]->getUID() != uid)
			continue;

		// If it is renderable we need to take into account the texture size of the renderable as well
		// as the position of the entity, otherwise we can straight up make a position comparison
		if (m_Entities[i]->checkRenderable())
		{
			// Take a pointer to the renderable
			Renderable* renderable_ptr = m_Entities[i]->getRenderable();

			// If the point is inside of the renderable and the Entity then return this Entity
			if (point.x >(m_Entities[i]->getPosition().x - renderable_ptr->getTexture()->getSize().y) &&
				point.y > (m_Entities[i]->getPosition().y - renderable_ptr->getTexture()->getSize().y) &&
				point.x < (m_Entities[i]->getPosition().x + renderable_ptr->getTexture()->getSize().x) &&
				point.y < (m_Entities[i]->getPosition().y + renderable_ptr->getTexture()->getSize().y))
			{
				return m_Entities[i];
			}
		}
		else
		{
			// If the point is equal to the position of the Entity return it
			if (point == m_Entities[i]->getPosition())
				return m_Entities[i];
		}
	}

	// Otherwise we have no Entity at this position
	return nullptr;
}

Entity* GameScene::getEntityClosestToPoint(sf::Vector2f point)
{
	// If Entities vector is empty, return nothing
	if (m_Entities.size() == 0)
		return nullptr;

	// Sample first Entity
	Entity* closest = m_Entities[0];
	float distance = lengthSq(point - closest->getPosition());

	// Find out if this really is the closest Entity
	for (uint32_t i = 0; i < m_Entities.size(); i++)
	{
		if (lengthSq(point - m_Entities[i]->getPosition()) < distance)
		{
			closest  = m_Entities[i];
			distance = lengthSq(point - m_Entities[i]->getPosition());
		}
	}

	// Return closest Entity
	return closest;
}

Entity* GameScene::getEntityClosestToPointWithUID(sf::Vector2f point, std::string uid)
{
	// If Culling vector is empty, return nothing
	if (m_Entities.size() == 0)
		return nullptr;

	// Sample first Entity
	Entity* closest = m_Entities[0];
	float distance = lengthSq(point - closest->getPosition());

	// Find out if this really is the closest Entity
	for (uint32_t i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i]->getUID() == uid &&
			lengthSq(point - m_Entities[i]->getPosition()) < distance)
		{
			closest = m_Entities[i];
			distance = lengthSq(point - m_Entities[i]->getPosition());
		}
	}

	// Return closest Entity
	if (closest->getUID() == uid)
		return closest;
	else
		return nullptr;
}

Entity* GameScene::getEntityWithUID(std::string uid)
{
	// Iterate over entities, if we have a UID match return that result
	for (auto entity : m_Entities)
	{
		if (entity->getUID() == uid)
			return entity;
	}

	// Otherwise return null
	return nullptr;
}

std::vector<Entity*> GameScene::getAllEntities()
{
	return m_Entities;
}
