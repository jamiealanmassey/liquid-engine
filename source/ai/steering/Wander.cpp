#include "Wander.h"
#include "../Agent.h"
#include "../../common/Entity.h"
#include "../../utilities/Random.h"

namespace liquid {
namespace ai {

    Wander::Wander()
    {
        mCircleDistance = 6.0f;
        mCircleRadius = 8.0f;
        mWanderAngle = 0.0f;
        mAngleChange = 1.0f;
    }

    Wander::~Wander()
    {
    }

    shape::Vector2& Wander::getSteeringForce(Agent& agent)
    {
        shape::Vector2 centre = agent.getVelocity();
        centre = centre.normalise();
        centre.scale(mCircleDistance);

        shape::Vector2 displacement = shape::Vector2(0, -1);
        displacement.scale(mCircleRadius);
        displacement = calculateAngle(displacement, mWanderAngle);

        mWanderAngle += (utilities::Random::instance().randomRange(0, 1) * mAngleChange) - (mAngleChange * .5f);
        return shape::Vector2(centre + displacement);
    }

    shape::Vector2& Wander::calculateAngle(shape::Vector2& v, float angle)
    {
        float magnitude = v.getMagnitude();
        float angleX = std::cos(angle) * magnitude;
        float angleY = std::sin(angle) * magnitude;
        return shape::Vector2(angleX, angleY);
    }

    void Wander::setCircleDistance(float circleDistance)
    {
        mCircleDistance = circleDistance;
    }

    void Wander::setCircleRadius(float circleRadius)
    {
        mCircleRadius = circleRadius;
    }

    void Wander::setAngleChange(float angleChange)
    {
        mAngleChange = angleChange;
    }

    const float Wander::getCircleDistance() const
    {
        return mCircleDistance;
    }

    const float Wander::getCircleRadius() const
    {
        return mCircleRadius;
    }

    const float Wander::getAngleChange() const
    {
        return mAngleChange;
    }

    const float Wander::getWanderAngle() const
    {
        return mWanderAngle;
    }

}}
