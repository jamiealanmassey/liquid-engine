#include "LuaFuncs.h"
#include "GameManager.h"
#include "GameScene.h"
#include "LuaManager.h"
#include "../ai/Agent.h"
#include "../utilities/DeltaTime.h"
#include "../graphics/ICamera.h"

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
            .addFunction("removeChild", luaRemoveChild)

            .addFunction("loadBehaviourTree", luaLoadBehaviourTree)
            .addFunction("setMaxVelocity", luaSetMaxVelocity)
            .addFunction("getVelocityX", luaGetVelocityX)
            .addFunction("getVelocityY", luaGetVelocityY)
            .addFunction("getMaxVelocity", luaGetMaxVelocity)
            
            .addFunction("wander", luaWander)
            .addFunction("seek", luaSeek)
            .addFunction("flee", luaFlee)
            .addFunction("evade", luaEvade)
            .addFunction("pursue", luaPursue)

            .addFunction("setCameraCentre", luaSetCameraCentre)
            .addFunction("setCameraSize", luaSetCameraSize)
            .addFunction("setCameraRotation", luaSetCameraRotation)
            .addFunction("shakeCamera", luaShakeCamera)

            .addFunction("createRectangle", luaCreateRectangle)
            .addFunction("createCircle", luaCreateCircle)
            .addFunction("createLineSegment", luaCreateLineSegment)
            
            .addFunction("getDeltaTime", luaGetDeltaTime);
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

    void LuaFuncs::luaLoadBehaviourTree(std::string entity, std::string xmlBT)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr && entityPtr->getAIAgent())
            entityPtr->getAIAgent()->loadBehaviourTree(xmlBT);
    }

    void LuaFuncs::luaSetMaxVelocity(std::string entity, float maxVelocity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr && entityPtr->getAIAgent())
            entityPtr->getAIAgent()->setMaxVelocity(maxVelocity);
    }

    float LuaFuncs::luaGetVelocityX(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr && entityPtr->getAIAgent())
            return entityPtr->getAIAgent()->getVelocityX();

        return 0.f;
    }

    float LuaFuncs::luaGetVelocityY(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr && entityPtr->getAIAgent())
            return entityPtr->getAIAgent()->getVelocityY();

        return 0.f;
    }

    float LuaFuncs::luaGetMaxVelocity(std::string entity)
    {
        Entity* entityPtr = LuaFuncs::getEntity(entity);

        if (entityPtr != nullptr && entityPtr->getAIAgent())
            return entityPtr->getAIAgent()->getMaxVelocity();

        return 0.f;
    }

    void LuaFuncs::luaWander(std::string entity)
    {
        ai::Agent* agent = getEntity(entity)->getAIAgent();

        if (agent != nullptr)
            agent->getSteeringManager()->wander();
    }

    void LuaFuncs::luaSeek(std::string entity, float targetX, float targetY)
    {
        ai::Agent* agent = getEntity(entity)->getAIAgent();

        if (agent != nullptr)
            agent->getSteeringManager()->seek(shape::Vector2(targetX, targetY));
    }

    void LuaFuncs::luaFlee(std::string entity, float targetX, float targetY)
    {
        ai::Agent* agent = getEntity(entity)->getAIAgent();

        if (agent != nullptr)
            agent->getSteeringManager()->flee(shape::Vector2(targetX, targetY));
    }

    void LuaFuncs::luaEvade(std::string entity, std::string targetEntity)
    {
        ai::Agent* agent0 = getEntity(entity)->getAIAgent();
        ai::Agent* agent1 = getEntity(targetEntity)->getAIAgent();

        if (agent0 != nullptr && agent1 != nullptr)
            agent0->getSteeringManager()->evade(agent1);
    }

    void LuaFuncs::luaPursue(std::string entity, std::string targetEntity)
    {
        ai::Agent* agent0 = getEntity(entity)->getAIAgent();
        ai::Agent* agent1 = getEntity(targetEntity)->getAIAgent();

        if (agent0 != nullptr && agent1 != nullptr)
            agent0->getSteeringManager()->pursue(agent1);
    }

    void LuaFuncs::luaSetCameraCentre(float x, float y)
    {
        graphics::ICamera* camera = GameManager::instance().getRendererClass()->getCamera();
        camera->setCentre({ x, y });
    }

    void LuaFuncs::luaSetCameraSize(float w, float h)
    {
        graphics::ICamera* camera = GameManager::instance().getRendererClass()->getCamera();
        camera->setDimensions({ w, h });
    }

    void LuaFuncs::luaSetCameraRotation(float rotation)
    {
        graphics::ICamera* camera = GameManager::instance().getRendererClass()->getCamera();
        camera->setRotation(rotation);
    }

    void LuaFuncs::luaShakeCamera(float duration, float radius, int32_t axis)
    {
        graphics::ICamera* camera = GameManager::instance().getRendererClass()->getCamera();
        camera->shake(duration, radius, (graphics::ICamera::eShakeAxis)axis);
    }

    shape::Rectangle LuaFuncs::luaCreateRectangle(float x, float y, float w, float h)
    {
        shape::Rectangle rectangle;
        rectangle.setRectangle(x, y, w, h);
        return rectangle;
    }

    shape::Circle LuaFuncs::luaCreateCircle(float x, float y, float radius)
    {
        shape::Circle circle;
        circle.setCircle(x, y, radius);
        return circle;
    }

    shape::LineSegment LuaFuncs::luaCreateLineSegment(float x1, float y1, float x2, float y2)
    {
        shape::LineSegment lineSegment(x1, y1, x2, y2);
        return lineSegment;
    }

    float LuaFuncs::luaGetDeltaTime()
    {
        return utilities::DeltaTime::DELTA;
    }

    Entity* LuaFuncs::getEntity(std::string entity)
    {
        GameScene* scene = GameManager::instance().peekGameSceneFront();
        return scene->getEntityWithUID(entity);
    }

}}
