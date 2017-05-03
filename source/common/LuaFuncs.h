#include "Entity.h"

namespace liquid { namespace common {
#ifndef _LUAFUNCS_H
#define _LUAFUNCS_H

class LuaFuncs
{
public:
    static void registerFunctions();

    static void luaSetPosition(std::string entity, float x, float y);
    static void luaAddPosition(std::string entity, float x, float y);
    static void luaSetSize(std::string entity, float w, float h);
    static bool luaIsPointInside(std::string entity, float x, float y);
    static void luaSleep(std::string entity);
    static void luaWake(std::string entity);
    static void luaKill(std::string entity);
    static void luaSetUID(std::string entity, std::string uid);
    static float luaGetPositionX(std::string entity);
    static float luaGetPositionY(std::string entity);
    static std::string luaGetUID(std::string entity);
    static void luaAddChild(std::string entity, std::string child);
    static void luaRemoveChild(std::string entity, std::string child);
    
    static Entity* getEntity(std::string entity);
};

#endif // _LUAFUNCS_H
}}
