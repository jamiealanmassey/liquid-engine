#include "Agent.h"
#include "../common/Entity.h"

namespace liquid {
namespace ai {

    Agent::Agent()
    {
        mVelocityX = nullptr;
        mVelocityY = nullptr;
        mVisionDistance = 0.0f;
        mEntityPtr = nullptr;
    }

    Agent::~Agent()
    {
    }

    void Agent::update()
    {
        // TODO: Update priority and Steering Behaviours
    }

    void Agent::setVelocityX(float* velocityX)
    {
        mVelocityX = velocityX;
    }

    void Agent::setVelocityY(float* velocityY)
    {
        mVelocityY = velocityY;
    }

    void Agent::setVisionDistance(float visionDist)
    {
        mVisionDistance = visionDist;
    }

    void Agent::setVisionCone(shape::Vector2& v1, shape::Vector2& v2)
    {
        mVisionCone[0] = v1;
        mVisionCone[1] = v2;
    }

    void Agent::setMaxVelocity(float maxVelocity)
    {
        mMaxVelocity = maxVelocity;
    }

    void Agent::setTargetAgent(Agent* targetAgent)
    {
        mTargetAgent = targetAgent;
    }

    void Agent::setEntityPtr(common::Entity* entityPtr)
    {
        mEntityPtr = entityPtr;
    }

    const float Agent::getVelocityX() const
    {
        return *mVelocityX;
    }

    const float Agent::getVelocityY() const
    {
        return *mVelocityY;
    }

    const float Agent::getVisionDistance() const
    {
        return mVisionDistance;
    }

    const float Agent::getMaxVelocity() const
    {
        return mMaxVelocity;
    }

    Agent* Agent::getTargetAgent() const
    {
        return mTargetAgent;
    }

    shape::Vector2& Agent::getVelocity() const
    {
        return shape::Vector2(*mVelocityX, *mVelocityY);
    }

    common::Entity* Agent::getEntityPtr() const
    {
        return mEntityPtr;
    }

}}
