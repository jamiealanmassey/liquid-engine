#include <string>

namespace liquid { namespace common {
#ifndef _LUAINSTANCE_H
#define _LUAINSTANCE_H

/** 
 * \class LuaInstance
 *
 * \ingroup Common
 * \brief Managing class to run and control LUA scripts via LuaBridge
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 10/04/2017
 *
 */

// TODO: Link and initialise LuaBridge
class LuaInstance
{
public:
    LuaInstance();
    ~LuaInstance();

    void initialise();
    bool runScript(std::string scriptLoc);
    virtual void registerFunctions();

    // luabridge::lua_State* getLuaState();

protected:
    // luabridge::lua_State* mLuaState;
};

#endif // _LUAINSTANCE_H
}}
