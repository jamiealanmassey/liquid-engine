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

    shape::Vector2& Seek::getSteeringForce(Agent& agent, shape::Vector2& targetPosition, shape::Vector2& targetDirection)
    {
        common::Entity* entity = agent.getEntityPtr();
        shape::Vector2 position = shape::Vector2(entity->getPositionX(), entity->getPositionY());
        shape::Vector2 difference = shape::Vector2(targetPosition - position);

        difference = difference.normalise();
        difference.scale(agent.getMaxVelocity());

        return (difference - agent.getVelocity());
    }

}}
