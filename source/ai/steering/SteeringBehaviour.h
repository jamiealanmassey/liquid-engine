#include "../../shapes/Vector2.h"

namespace liquid { namespace ai {
#ifndef _STEERINGBEHAVIOUR_H
#define _STEERINGBEHAVIOUR_H

class Agent;
class SteeringBehaviour
{
public:
    SteeringBehaviour() {}
    ~SteeringBehaviour() {}

    virtual shape::Vector2& getSteeringForce(Agent& agent, shape::Vector2& targetPosition, shape::Vector2& targetDirection) = 0;
};

#endif // _STEERINGBEHAVIOUR_H
}}
