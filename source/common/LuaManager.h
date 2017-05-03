extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <string>
#include <LuaBridge/LuaBridge.h>

namespace liquid { namespace common {
#ifndef _LUAMANAGER_H
#define _LUAMANAGER_H

/** 
 * \class LuaManager
 *
 * \ingroup Common
 * \brief Managing class to run and control LUA scripts via LuaBridge
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 10/04/2017
 *
 */

class LuaManager
{
public:
    LuaManager();
    ~LuaManager();

    bool runScript(std::string script);

    lua_State* getLuaState();

    static LuaManager& instance();

protected:
    lua_State* mLuaState;
};

#endif // _LUAINSTANCE_H
}}
