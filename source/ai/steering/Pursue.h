#include "SteeringBehaviour.h"

namespace liquid {
namespace ai {
#ifndef _PURSUE_H
#define _PURSUE_H

class Pursue : public SteeringBehaviour
{
public:
    Pursue();
    ~Pursue();

    shape::Vector2& getSteeringForce(Agent& agent) override;

protected:
    uint32_t mPredictionSteps;
};

#endif // _PURSUE_H
}
}
