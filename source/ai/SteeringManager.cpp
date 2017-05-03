#include "SteeringManager.h"
#include "Agent.h"
#include "../common/Entity.h"
#include "../utilities/Random.h"

namespace liquid {
namespace ai {

    SteeringManager::SteeringManager(Agent* parentAgent) :
        mCircleDistance(6.0f),
        mCircleRadius(8.0f),
        mAngleChange(1.0f),
        mMaxForce(5.4f)
    {
        mWanderAngle = 0.f;
        mParentAgent = parentAgent;
        mSteeringForce = shape::VECTOR20;
    }

    SteeringManager::~SteeringManager()
    {
    }

    void SteeringManager::update()
    {
        shape::Vector2 velocity = mParentAgent->getVelocity();
        mSteeringForce = truncate(mSteeringForce, mMaxForce);
        mSteeringForce.scale(1 / mParentAgent->getMass());

        velocity += mSteeringForce;
        velocity = truncate(velocity, mParentAgent->getMaxVelocity());

        mSteeringVelocity = velocity;
        mSteeringForce = shape::VECTOR20;
    }

    void SteeringManager::reset()
    {
        mSteeringForce = shape::VECTOR20;
        mSteeringVelocity = shape::VECTOR20;
        mParentAgent->setVelocityX(0.f);
        mParentAgent->setVelocityY(0.f);
    }

    shape::Vector2 SteeringManager::wander()
    {
        shape::Vector2 centre, displacement, force;
        
        centre = mParentAgent->getVelocity();
        centre = centre.normalise();
        centre.scale(mCircleDistance);

        displacement = shape::Vector2(0.0f, -1.0f);
        displacement.scale(mCircleRadius);

        displacement = calculateAngle(displacement, mWanderAngle);
        mWanderAngle += utilities::Random::instance().randomRange(0.f, 1.f) * mAngleChange;
        mWanderAngle -= mAngleChange * .5f;

        force = centre + displacement;
        mSteeringForce += force;
        return force;
    }

    shape::Vector2 SteeringManager::seek(shape::Vector2& target, float slowingRadius)
    {
        shape::Vector2 desired, result;
        float distance;

        desired = target - getPosition(mParentAgent);
        distance = desired.getMagnitude();
        desired = desired.normalise();

        if (distance <= slowingRadius)
            desired.scale(mParentAgent->getMaxVelocity() * (distance / slowingRadius));
        else
            desired.scale(mParentAgent->getMaxVelocity());

        result = desired - mParentAgent->getVelocity();
        mSteeringForce += result;
        return result;
    }

    shape::Vector2 SteeringManager::flee(shape::Vector2& target)
    {
        shape::Vector2 desired = (getPosition(mParentAgent) - target).normalise();
        mSteeringForce += desired * mParentAgent->getMaxVelocity();
        return desired * mParentAgent->getMaxVelocity();
    }

    shape::Vector2 SteeringManager::evade(Agent* target)
    {
        shape::Vector2 distance, targetPosition, futurePosition;

        targetPosition = getPosition(target);
        distance = targetPosition - getPosition(mParentAgent);

        float updates = distance.getMagnitude() / mParentAgent->getMaxVelocity();
        futurePosition = targetPosition + target->getVelocity() * updates;

        return flee(futurePosition);
    }

    shape::Vector2 SteeringManager::pursue(Agent* target)
    {
        shape::Vector2 distance = getPosition(target) - getPosition(mParentAgent);
        shape::Vector2 velocity = target->getVelocity();
        
        velocity *= distance.getMagnitude() / mParentAgent->getMaxVelocity();
        return seek(getPosition(target) + velocity);
    }

    Agent* SteeringManager::getParentAgent() const
    {
        return mParentAgent;
    }

    shape::Vector2 SteeringManager::getSteeringForce() const
    {
        return mSteeringForce;
    }

    shape::Vector2 SteeringManager::getSteeringVelocity() const
    {
        return mSteeringVelocity;
    }

    shape::Vector2 SteeringManager::getPosition(Agent* agent)
    {
        float positionX = agent->getEntityPtr()->getPositionX();
        float positionY = agent->getEntityPtr()->getPositionY();

        return shape::Vector2(positionX, positionY);
    }

    shape::Vector2 SteeringManager::calculateAngle(shape::Vector2& v, float angle)
    {
        float magnitude = v.getMagnitude();
        float angleX = std::cos(angle) * magnitude;
        float angleY = std::sin(angle) * magnitude;
        return shape::Vector2(angleX, angleY);
    }

    shape::Vector2 SteeringManager::truncate(shape::Vector2& steering, float maxForce)
    {
        float force = maxForce / steering.getMagnitude();
        force = force < 1.0f ? force : 1.0f;
        return steering * force;
    }

}}
