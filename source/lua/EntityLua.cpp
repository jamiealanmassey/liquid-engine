#include "EntityLua.h"
#include "../common/GameScene.h"

void luaEntityBind()
{
	// Bind the most common functions for LUA
	luabridge::getGlobalNamespace(GameManager::instance().getLuaInstance()->getLuaState())
		.addFunction("checkRenderable",    &luaCheckRenderable)
		.addFunction("checkPhysics",	   &luaCheckPhysics)
		.addFunction("isPointInside",	   &luaIsPointInside)
		.addFunction("doEntitySleep",	   &luaDoEntitySleep)
		.addFunction("doEntityWake",	   &luaDoEntityWake)
		.addFunction("doEntityKill",	   &luaDoEntityKill)
		.addFunction("attachRenderable",   &luaAttachRenderable)
		.addFunction("setPosition",		   &luaSetPosition)
		.addFunction("addPosition",		   &luaAddPosition)
		.addFunction("addChild",		   &luaAddChild)
		.addFunction("getEntityType",	   &luaGetEntityType)
		.addFunction("getEntityState",	   &luaGetEntityState)
		.addFunction("getParentSceneName", &luaGetParentSceneName)
		.addFunction("getParentID",		   &luaGetParentID)
		.addFunction("getPosition",		   &luaGetPosition)
		.addFunction("hasChildren",		   &luaHasChildren);
}

bool luaCheckRenderable(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	return (entity && (entity->checkRenderable()));
}

bool luaCheckPhysics(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	return (entity && (entity->checkPhysics()));
}

bool luaIsPointInside(std::string entID, float x, float y)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	return (entity && (entity->isPointInside(sf::Vector2f(x, y))));
}

void luaDoEntitySleep(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		entity->sleep();
}

void luaDoEntityWake(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		entity->wake();
}

void luaDoEntityKill(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		entity->kill();
}

// TODO: Allow loading of renderables through XML definitions
void luaAttachRenderable(std::string entID, std::string texture, int32_t depth)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
	{
		Renderable* renderable = new Renderable(texture, depth);
		entity->attachRenderable(renderable);
	}
}

void luaSetPosition(std::string entID, float x, float y)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		entity->setPosition(x, y);
}

void luaAddPosition(std::string entID, float x, float y)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		entity->addPosition(x, y);
}

void luaAddChild(std::string entID, std::string childID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* parent = scene->getEntityWithUID(entID);
	Entity* child = scene->getEntityWithUID(childID);

	if (child && parent)
		parent->addChild(child);
}

int32_t	luaGetEntityType(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		return entity->getEntityType();
	else
		return -1;
}

int32_t	luaGetEntityState(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		return (int32_t)entity->getEntityState();
	else
		return (int32_t)Entity::eEntityState::ENTITYSTATE_DEAD;
}

std::string luaGetParentSceneName(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		return entity->getParentScene()->getStateName();
	else
		return "";
}

std::string luaGetParentID(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);
	Entity* parent = entity->getParent();

	if (parent)
		return parent->getUID();
	else
		return "";
}

sf::Vector2f luaGetPosition(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity)
		return entity->getPosition();
	else
		return sf::Vector2f();
}

bool luaHasChildren(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	return (entity && !entity->getChildren().empty());
}
