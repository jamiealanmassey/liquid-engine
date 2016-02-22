#ifndef _LUAINSTANCE_H
#define _LUAINSTANCE_H

#include <LuaBridge/LuaBridge.h>
#include <lua.hpp>

class LuaInstance
{
public:
	LuaInstance();
	~LuaInstance();

	/* Core lua functionality */
	void init();
	bool runScript(std::string script_file);

	/* Functions to register Lua Functions */
		    void registerLuaFunctions();
	virtual void registerLuaFunctionsUser() = 0;

protected:
	luabridge::lua_State* m_LuaState; ///< Holds a pointer to the LuaState
};

#endif // _LUAINSTANCE_H
