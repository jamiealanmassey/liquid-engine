#include "Seek.h"
#include "../Agent.h"
#include "../../common/Entity.h"

namespace liquid {
namespace ai {

    Seek::Seek()
    {
    }

    Seek::~Seek()
    {
    }

    shape::Vector2& Seek::getSteeringForce(Agent& agent)
    {
        common::Entity* entity = agent.getEntityPtr();
        Agent* targetAgent = agent.getTargetAgent();

        if (targetAgent == nullptr || targetAgent->getEntityPtr() == nullptr)
            return shape::Vector2();

        float targetX = targetAgent->getEntityPtr()->getPositionX();
        float targetY = targetAgent->getEntityPtr()->getPositionX();
        shape::Vector2 targetPosition(targetX, targetY);

        shape::Vector2 position = shape::Vector2(entity->getPositionX(), entity->getPositionY());
        shape::Vector2 difference = shape::Vector2(targetPosition - position);

        difference = difference.normalise();
        difference.scale(agent.getMaxVelocity());

        return (difference - agent.getVelocity());
    }

}}
