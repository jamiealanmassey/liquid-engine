#include "SteeringBehaviour.h"

namespace liquid {
namespace ai {
#ifndef _EVADE_H
#define _EVADE_H

class Evade : public SteeringBehaviour
{
public:
    Evade();
    ~Evade();

    shape::Vector2& getSteeringForce(Agent& agent) override;
};

#endif // _EVADE_H
}
}
