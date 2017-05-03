#include "SteeringBehaviour.h"

namespace liquid {
namespace ai {
#ifndef _FLEE_H
#define _FLEE_H

class Flee : public SteeringBehaviour
{
public:
    Flee();
    ~Flee();

    shape::Vector2& getSteeringForce(Agent& agent) override;
};

#endif // _FLEE_H
}
}
