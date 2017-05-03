#include "SteeringBehaviour.h"

namespace liquid {
namespace ai {
#ifndef _WANDER_H
#define _WANDER_H

class Wander : public SteeringBehaviour
{
public:
    Wander();
    ~Wander();

    shape::Vector2& getSteeringForce(Agent& agent) override;

    shape::Vector2& calculateAngle(shape::Vector2& v, float angle);

    void setCircleDistance(float circleDistance);
    void setCircleRadius(float circleRadius);
    void setAngleChange(float angleChange);

    const float getCircleDistance() const;
    const float getCircleRadius() const;
    const float getAngleChange() const;
    const float getWanderAngle() const;

protected:
    float mCircleDistance;
    float mCircleRadius;
    float mAngleChange;
    float mWanderAngle;
};

#endif // _WANDER_H
}
}
