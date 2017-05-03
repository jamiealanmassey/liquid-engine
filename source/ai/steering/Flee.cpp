#include "Flee.h"
#include "../Agent.h"
#include "../../common/Entity.h"

namespace liquid {
namespace ai {

    Flee::Flee()
    {
    }

    Flee::~Flee()
    {
    }

    shape::Vector2& Flee::getSteeringForce(Agent& agent)
    {
        common::Entity* entity = agent.getEntityPtr();
        Agent* targetAgent = agent.getTargetAgent();

        if (targetAgent == nullptr || targetAgent->getEntityPtr() == nullptr)
            return shape::Vector2();

        float targetX = targetAgent->getEntityPtr()->getPositionX();
        float targetY = targetAgent->getEntityPtr()->getPositionX();
        shape::Vector2 targetPosition(targetX, targetY);

        shape::Vector2 position = shape::Vector2(entity->getPositionX(), entity->getPositionY());
        shape::Vector2 difference = shape::Vector2(position - targetPosition);

        difference = difference.normalise();
        difference.scale(agent.getMaxVelocity());

        return (difference - agent.getVelocity());
    }

}}
