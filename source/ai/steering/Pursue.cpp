#include "Pursue.h"
#include "../Agent.h"
#include "../../common/Entity.h"

namespace liquid {
namespace ai {

    Pursue::Pursue()
    {
    }

    Pursue::~Pursue()
    {
    }

    shape::Vector2& Pursue::getSteeringForce(Agent& agent)
    {
        common::Entity* entity = agent.getEntityPtr();
        Agent* targetAgent = agent.getTargetAgent();

        if (targetAgent == nullptr || targetAgent->getEntityPtr() == nullptr)
            return shape::Vector2();

        float targetX = targetAgent->getEntityPtr()->getPositionX();
        float targetY = targetAgent->getEntityPtr()->getPositionX();
        float maxVelocity = agent.getMaxVelocity();

        shape::Vector2 targetPosition(targetX, targetY);
        shape::Vector2 position = shape::Vector2(entity->getPositionX(), entity->getPositionY());
        shape::Vector2 distance = shape::Vector2(targetPosition - position);

        float pursuit = distance.getMagnitude() / maxVelocity;
        shape::Vector2 predicted((targetPosition + targetAgent->getVelocity()) * pursuit);
        shape::Vector2 desired(predicted - position);

        desired = desired.normalise();
        desired.scale(maxVelocity);
        return (desired - agent.getVelocity());
    }

}}
