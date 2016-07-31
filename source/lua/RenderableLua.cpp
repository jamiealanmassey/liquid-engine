#include "RenderableLua.h"
#include "../common/GameScene.h"

void luaRenderableBind()
{
	// Bind the most common functions for LUA
	luabridge::getGlobalNamespace(GameManager::instance().getLuaInstance()->getLuaState())
		.addFunction("changeAnimation",		   &luaChangeAnimation)
		.addFunction("changeDefaultAnimation", &luaChangeDefaultAnimation)
		.addFunction("changeAnimationMode",	   &luaChangeAnimationMode)
		.addFunction("updateRotation",		   &luaUpdateRotation)
		.addFunction("setRenderableActive",    &luaSetRenderableActive)
		.addFunction("faceTarget",			   &luaFaceTarget)
		.addFunction("checkTextured",		   &luaCheckTextured)
		.addFunction("checkAnimated",		   &luaCheckAnimated)
		.addFunction("checkShaded",			   &luaCheckShaded)
		.addFunction("checkCentred",		   &luaCheckCentred)
		.addFunction("getSceneDepth",		   &luaGetSceneDepth)
		.addFunction("getDefaultStartFrame",   &luaGetDefaultStartFrame)
		.addFunction("getDefaultEndFrame",     &luaGetDefaultEndFrame)
		.addFunction("getCurrentFrame",		   &luaGetCurrentFrame)
		.addFunction("getStartFrame",		   &luaGetStartFrame)
		.addFunction("getEndFrame",			   &luaGetEndFrame)
		.addFunction("getTexturePath",		   &luaGetTexturePath)
		.addFunction("getAnimationPath",	   &luaGetAnimationPath)
		.addFunction("getDimensions",		   &luaGetDimensions);
}

void luaChangeAnimation(std::string entID, std::string name, int32_t begin, int32_t end)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity->checkRenderable())
		entity->getRenderable()->changeAnimation(name, begin, end);
}

void luaChangeDefaultAnimation(std::string entID, std::string name, int32_t begin, int32_t end)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity->checkRenderable())
		entity->getRenderable()->changeDefaultAnimation(name, begin, end);
}

void luaChangeAnimationMode(std::string entID, int32_t mode)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity->checkRenderable())
		entity->getRenderable()->changeAnimationMode((Renderable::eAnimationMode)mode);
}

void luaUpdateRotation(std::string entID, float angle)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity->checkRenderable())
		entity->getRenderable()->updateRotation(angle);
}

void luaSetRenderableActive(std::string entID, bool flag)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity->checkRenderable())
		entity->getRenderable()->setActive(flag);
}

float luaFaceTarget(std::string entID, float x, float y)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity->checkRenderable())
		return entity->getRenderable()->faceTarget(sf::Vector2f(x, y));
	else
		return 0.0f;
}

bool luaCheckTextured(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	return (entity && entity->checkRenderable() && 
		(entity->getRenderable()->checkTextured()));
}

bool luaCheckAnimated(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	return (entity && entity->checkRenderable() &&
		(entity->getRenderable()->checkAnimated()));
}

bool luaCheckShaded(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	return (entity && entity->checkRenderable() &&
		(entity->getRenderable()->checkShaded()));
}

bool luaCheckCentred(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	return (entity && entity->checkRenderable() &&
		(entity->getRenderable()->checkCentred()));
}

int32_t luaGetSceneDepth(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getSceneDepth();
}

int32_t luaGetDefaultStartFrame(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getDefaultStartFrame();
}

int32_t luaGetDefaultEndFrame(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getDefaultEndFrame();
}

int32_t luaGetCurrentFrame(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getCurrentFrame();
}

int32_t luaGetStartFrame(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getStartFrame();
}

int32_t luaGetEndFrame(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getEndFrame();
}

std::string luaGetTexturePath(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getTexturePath();
}

std::string luaGetAnimationPath(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getAnimationPath();
}

sf::Vector2f luaGetDimensions(std::string entID)
{
	GameScene* scene = GameManager::instance().peekGameSceneFront();
	Entity* entity = scene->getEntityWithUID(entID);

	if (entity && entity->checkRenderable())
		return entity->getRenderable()->getDimensions();
}
