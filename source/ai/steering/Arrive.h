#include "SteeringBehaviour.h"

namespace liquid {
namespace ai {
#ifndef _ARRIVE_H
#define _ARRIVE_H

class Arrive : public SteeringBehaviour
{
public:
    Arrive();
    ~Arrive();

    shape::Vector2& getSteeringForce(Agent& agent) override;

    void setSlowingRadius(float slowingRadius);

    const float getSlowingRadius() const;

protected:
    float mSlowingRadius;
};

#endif // _ARRIVE_H
}
}
