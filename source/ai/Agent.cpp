#include "Agent.h"
#include "../common/Entity.h"

namespace liquid {
namespace ai {

    Agent::Agent()
    {
        mVelocityX = 0.f;
        mVelocityY = 0.f;
        mVisionDistance = 0.0f;
        mEntityPtr = nullptr;
        mSteeringManager = new SteeringManager(this);
        mBehaviourTree = nullptr;
    }

    Agent::~Agent()
    {
        delete mSteeringManager;
    }

    void Agent::update()
    {
        if (mBehaviourTree != nullptr)
            mBehaviourTree->process();

        mSteeringManager->update();

        shape::Vector2 velocity(mSteeringManager->getSteeringVelocity());
        mVelocityX = velocity.getVectorX();
        mVelocityY = velocity.getVectorY();
    }

    void Agent::loadBehaviourTree(std::string xmlBehaviourTree)
    {
        if (mBehaviourTree == nullptr)
            mBehaviourTree = new BehaviourTree();

        parser::ParserXML xmlBehaviourParser;
        xmlBehaviourParser.parseFile(xmlBehaviourTree);

        BehaviourTreeParser parser(xmlBehaviourParser);
        mBehaviourTree->setNodeRoot(parser.getConstructedNode());
    }

    void Agent::setVelocityX(float velocityX)
    {
        mVelocityX = velocityX;
    }

    void Agent::setVelocityY(float velocityY)
    {
        mVelocityY = velocityY;
    }

    void Agent::setMass(float mass)
    {
        mMass = mass;
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

    void Agent::setEntityPtr(common::Entity* entityPtr)
    {
        mEntityPtr = entityPtr;
    }

    const float Agent::getVelocityX() const
    {
        return mVelocityX;
    }

    const float Agent::getVelocityY() const
    {
        return mVelocityY;
    }

    const float Agent::getMass() const
    {
        return mMass;
    }

    const float Agent::getVisionDistance() const
    {
        return mVisionDistance;
    }

    const float Agent::getMaxVelocity() const
    {
        return mMaxVelocity;
    }

    shape::Vector2& Agent::getVelocity() const
    {
        return shape::Vector2(mVelocityX, mVelocityY);
    }

    common::Entity* Agent::getEntityPtr() const
    {
        return mEntityPtr;
    }

}}
