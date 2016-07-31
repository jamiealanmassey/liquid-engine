#ifndef _LUAINSTANCE_H
#define _LUAINSTANCE_H

#include <LuaBridge/LuaBridge.h>
#include <lua.hpp>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class LuaInstance
{
public:
	LuaInstance();
	~LuaInstance();

	/* Core lua functionality */
	void initialise();
	bool runScript(std::string script_file);

	/* Functions to register Lua Functions */
		    void registerLuaFunctions();
	virtual void registerLuaFunctionsUser() {}

	luabridge::lua_State* getLuaState() { return m_LuaState; }

protected:
	luabridge::lua_State* m_LuaState; ///< Holds a pointer to the LuaState
};

#endif // _LUAINSTANCE_H
