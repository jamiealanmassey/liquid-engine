#include "LuaManager.h"
#include "LuaFuncs.h"
#include <iostream>

namespace liquid {
namespace common {

    LuaManager::LuaManager()
    {
        mLuaState = luaL_newstate();
        luaL_openlibs(mLuaState);
    }

    LuaManager::~LuaManager()
    {}

    bool LuaManager::runScript(std::string script)
    {
        if (script == "")
            return false;

        int32_t message = 0;
        message = luaL_loadfile(mLuaState, script.c_str());

        if (message == LUA_ERRFILE)
            std::cout << "Could not find or access script" << std::endl;

        else if (message == LUA_ERRSYNTAX)
            std::cout << "Syntax Error: " << lua_tostring(mLuaState, -1) << std::endl;

        if (lua_pcall(mLuaState, 0, LUA_MULTRET, 0) != 0)
        {
            std::cout << "Could not run script: " << lua_tostring(mLuaState, -1) << std::endl;
            return false;
        }

        return true;
    }

    lua_State* LuaManager::getLuaState()
    {
        return mLuaState;
    }

    LuaManager& LuaManager::instance()
    {
        static LuaManager singleton;
        return singleton;
    }

}}
