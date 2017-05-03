#include "LuaFuncs.h"
#include "GameManager.h"
#include "GameScene.h"
#include "LuaManager.h"

namespace liquid {
namespace common {

    void LuaFuncs::registerFunctions()
    {
        luabridge::getGlobalNamespace(LuaManager::instance().getLuaState())
            .addFunction("setPosition", luaSetPosition)
            .addFunction("addPosition", luaAddPosition)
            .addFunction("setSize", luaSetSize)
            .addFunction("isPointInside", luaIsPointInside)
            .addFunction("sleep", luaSleep)
            .addFunction("wake", luaWake)
            .addFunction("kill", luaKill)
            .addFunction("setUID", luaSetUID)
            .addFunction("getPositionX", luaGetPositionX)
            .addFunction("getPositionY", luaGetPositionY)
            .addFunction("getUID", luaGetUID)
            .addFunction("addChild", luaAddChild)
            .addFunction("removeChild", luaRemoveChild);
    }

    void LuaFuncs::luaSetPosition(std::string entity, float x, float y)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            entityPtr->setPosition(x, y);
    }

    void LuaFuncs::luaAddPosition(std::string entity, float x, float y)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            entityPtr->addPosition(x, y);
    }

    void LuaFuncs::luaSetSize(std::string entity, float w, float h)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            entityPtr->setSize(w, h);
    }

    bool LuaFuncs::luaIsPointInside(std::string entity, float x, float y)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            return entityPtr->isPointInside(x, y);

        return false;
    }

    void LuaFuncs::luaSleep(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            entityPtr->sleep();
    }

    void LuaFuncs::luaWake(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            entityPtr->wake();
    }

    void LuaFuncs::luaKill(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            entityPtr->kill();
    }

    void LuaFuncs::luaSetUID(std::string entity, std::string uid)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            entityPtr->setEntityUID(uid);
    }

    float LuaFuncs::luaGetPositionX(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            return entityPtr->getPositionX();

        return 0.f;
    }

    float LuaFuncs::luaGetPositionY(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            return entityPtr->getPositionY();

        return 0.f;
    }

    std::string LuaFuncs::luaGetUID(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr)
            return entityPtr->getEntityUID();

        return "";
    }

    void LuaFuncs::luaAddChild(std::string entity, std::string child)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);
        Entity* entityChild = LuaFuncs::getEntity(child);

        if (entityPtr != nullptr && entityChild != nullptr)
            entityChild->setParentEntity(entityPtr);
    }

    void LuaFuncs::luaRemoveChild(std::string entity, std::string child)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);
        Entity* entityChild = LuaFuncs::getEntity(child);

        if (entityPtr != nullptr && entityChild != nullptr)
            entityChild->setParentEntity(nullptr);
    }

    Entity* LuaFuncs::getEntity(std::string entity)
    {
        GameScene* scene = GameManager::instance().peekGameSceneFront();
        return scene->getEntityWithUID(entity);
    }

}}
