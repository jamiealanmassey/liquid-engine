#include "../shapes/Vector2.h"

namespace liquid { namespace ai {
#ifndef _STEERINGMANAGER_H
#define _STEERINGMANAGER_H

class Agent;
class SteeringManager
{
public:
    SteeringManager(Agent* parentAgent);
    ~SteeringManager();

    void update();
    void reset();

    shape::Vector2 wander();
    shape::Vector2 seek(shape::Vector2& target, float slowingRadius = 0.f);
    shape::Vector2 flee(shape::Vector2& target);
    shape::Vector2 evade(Agent* target);
    shape::Vector2 pursue(Agent* target);

    Agent* getParentAgent() const;
    shape::Vector2 getSteeringForce() const;
    shape::Vector2 getSteeringVelocity() const;

protected:
    shape::Vector2 getPosition(Agent* agent);
    shape::Vector2 calculateAngle(shape::Vector2& v, float angle);
    shape::Vector2 truncate(shape::Vector2& steering, float maxForce);

protected:
    float mWanderAngle;
    Agent* mParentAgent;
    shape::Vector2 mSteeringForce;
    shape::Vector2 mSteeringVelocity;

protected:
    const float mCircleDistance;
    const float mCircleRadius;
    const float mAngleChange;
    const float mMaxForce;
};

#endif // _STEERINGMANAGER_H
}}
