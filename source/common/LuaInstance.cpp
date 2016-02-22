#include "LuaInstance.h"
#include "Entity.h"
#include "GameScene.h"
#include "../utilities/Vectors.h"
#include "../graphics/Renderable.h"

/////////////////////////////////////////////////
float luaf_getDistance(sf::Vector2f v1, sf::Vector2f v2)
{
	return length(v1 - v2);
}

float luaf_getLength(sf::Vector2f v)
{
	return length(v);
}

sf::Vector2f luaf_getNormalized(sf::Vector2f v)
{
	return normalize(v);
}

sf::Vector2f luaf_getRandomVector(float min_x, float min_y, float max_x, float max_y)
{
	return sf::Vector2f(); // TODO
}

/////////////////////////////////////////////////
LuaInstance::LuaInstance()
{
}

LuaInstance::~LuaInstance()
{
}

void LuaInstance::init()
{
	// Create new lua_State and instantiate connected functions
	m_LuaState = luabridge::luaL_newstate();
	luabridge::luaL_openlibs(m_LuaState);
	registerLuaFunctions();
}

bool LuaInstance::runScript(std::string script_file)
{
	int32_t message = 0;

	if ((message = luabridge::luaL_loadfile(m_LuaState, script_file.c_str())) != 0)
	{
		if (message == LUA_ERRFILE)
		{
			std::cout << "Cannot find or access LUA script" << script_file << std::endl;
			return false;
		}
		else if (message == LUA_ERRSYNTAX)
		{
			std::cout << "LUA Syntax Error: " << luabridge::lua_tostring(m_LuaState, -1) << std::endl;
			return false;
		}

		if (luabridge::lua_pcall(m_LuaState, 0, LUA_MULTRET, 0) != 0)
		{
			std::cout << "Could not run LUA script " << script_file << ". Error: "
				<< luabridge::lua_tostring(m_LuaState, -1) << std::endl;

			return false;
		}
	}

	return true;
}

void LuaInstance::registerLuaFunctions()
{
	luabridge::getGlobalNamespace(m_LuaState)
		.addFunction("getDistance", luaf_getDistance)
		.addFunction("getLength", luaf_getLength)
		.addFunction("getNormalized", luaf_getNormalized)

		.beginClass<sf::Vector2f>("Vector2f")
			.addConstructor<void(*)(float, float)>()
			.addData("x", &sf::Vector2f::x)
			.addData("y", &sf::Vector2f::y)
		.endClass();

	registerLuaFunctionsUser();
}
