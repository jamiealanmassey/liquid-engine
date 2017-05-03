#include "Arrive.h"
#include "../Agent.h"
#include "../../common/Entity.h"

namespace liquid {
namespace ai {

    Arrive::Arrive()
    {
    }

    Arrive::~Arrive()
    {
    }

    shape::Vector2& Arrive::getSteeringForce(Agent& agent)
    {
        common::Entity* entity = agent.getEntityPtr();
        Agent* targetAgent = agent.getTargetAgent();

        if (targetAgent == nullptr || targetAgent->getEntityPtr() == nullptr)
            return shape::Vector2();

        float targetX = targetAgent->getEntityPtr()->getPositionX();
        float targetY = targetAgent->getEntityPtr()->getPositionX();
        shape::Vector2 targetPosition(targetX, targetY);

        shape::Vector2 position = shape::Vector2(entity->getPositionX(), entity->getPositionY());
        shape::Vector2 desired = shape::Vector2(targetPosition - position);
        float magnitude = desired.getMagnitude();

        if (magnitude < mSlowingRadius)
            desired = desired.normalise() * agent.getMaxVelocity() * (magnitude / mSlowingRadius);
        else
            desired = desired.normalise() * agent.getMaxVelocity();

        return (desired - agent.getVelocity());
    }

    void Arrive::setSlowingRadius(float slowingRadius)
    {
        mSlowingRadius = slowingRadius;
    }

    const float Arrive::getSlowingRadius() const
    {
        return mSlowingRadius;
    }

}}
