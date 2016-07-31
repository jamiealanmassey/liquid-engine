#include "ParticleEmitterLua.h"
#include "../common/GameManager.h"
#include "../graphics/ParticleEmitter.h"
#include "../utilities/IDGenerator.h"

void luaParticleEmitterBind()
{
	// Bind the most common functions for LUA
	luabridge::getGlobalNamespace(GameManager::instance().getLuaInstance()->getLuaState())
		.addFunction("createParticleEmitter", &luaCreateParticleEmitter);
}

void luaCreateParticleEmitter(std::string id, float x, float y, std::string xml)
{
	ParticleEmitter* emitter = new ParticleEmitter(id, sf::Vector2f(x, y), xml);
	GameManager::instance().peekGameSceneFront()->addEntity(emitter);
}
