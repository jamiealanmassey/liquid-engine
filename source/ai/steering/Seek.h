#include "SteeringBehaviour.h"

namespace liquid { namespace ai {
#ifndef _SEEK_H
#define _SEEK_H

class Seek : public SteeringBehaviour
{
public:
    Seek();
    ~Seek();

    shape::Vector2& getSteeringForce(Agent& agent, shape::Vector2& targetPosition, shape::Vector2& targetDirection) override;
};

#endif // _SEEK_H
}}
