#include "Entity.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include "../shapes/LineSegment.h"
#include "../common/Camera.h"
#include "../ai/BehaviourContext.h"
#include "../ai/BehaviourTree.h"

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
    
    static void luaLoadBehaviourTree(std::string entity, std::string xmlBT);
    static void luaSetMaxVelocity(std::string entity, float maxVelocity);
    static float luaGetVelocityX(std::string entity);
    static float luaGetVelocityY(std::string entity);
    static float luaGetMaxVelocity(std::string entity);

    static void luaWander(std::string entity);
    static void luaSeek(std::string entity, float targetX, float targetY);
    static void luaFlee(std::string entity, float targetX, float targetY);
    static void luaEvade(std::string entity, std::string targetEntity);
    static void luaPursue(std::string entity, std::string targetEntity);

    static void luaSetCameraCentre(float x, float y);
    static void luaSetCameraSize(float w, float h);
    static void luaSetCameraRotation(float rotation);
    static void luaShakeCamera(float duration, float radius, int32_t axis);

    static shape::Rectangle luaCreateRectangle(float x, float y, float w, float h);
    static shape::Circle luaCreateCircle(float x, float y, float radius);
    static shape::LineSegment luaCreateLineSegment(float x1, float y1, float x2, float y2);

    static float luaGetDeltaTime();
    static void luaPrintLn(std::string line);
    static Entity* getEntity(std::string entity);
};

#endif // _LUAFUNCS_H
}}
