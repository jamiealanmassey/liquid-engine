#include "SteeringManager.h"
#include "BehaviourTree.h"
#include "BehaviourTreeParser.h"
#include "../shapes/Vector2.h"
#include "../shapes/Rectangle.h"
#include "../parser/ParserXML.h"
#include <functional>

namespace liquid { namespace common { class Entity; } }

namespace liquid { namespace ai {
#ifndef _AGENT_H
#define _AGENT_H

class Agent
{
public:
    typedef std::function<void(float, float)> VelocityFunc;

public:
    Agent();
    ~Agent();

    virtual void update();

    void loadBehaviourTree(std::string xmlBehaviourTree);

    void setVelocityX(float velocityX);
    void setVelocityY(float velocityY);
    void setMass(float mass);

    void setVisionDistance(float visionDist);
    void setVisionCone(shape::Vector2& v1, shape::Vector2& v2);
    void setMaxVelocity(float maxVelocity);
    void setEntityPtr(common::Entity* entityPtr);
    void setBehaviourTree(BehaviourTree* behaviourTree);
    void setVelocityFunc(VelocityFunc func);

    const float getVelocityX() const;
    const float getVelocityY() const;
    const float getMass() const;
    const float getVisionDistance() const;
    const float getMaxVelocity() const;
    
    shape::Vector2 getVelocity() const;
    common::Entity* getEntityPtr() const;
    SteeringManager* getSteeringManager() const;
    BehaviourTree* getBehaviourTree() const;

public:
    shape::Vector2 target;

protected:
    float mVelocityX;
    float mVelocityY;
    float mMass;
    float mVisionDistance;
    float mMaxVelocity;
    shape::Vector2 mSteeringForce;
    shape::Vector2 mVisionCone[2];
    common::Entity* mEntityPtr;
    SteeringManager* mSteeringManager;
    BehaviourTree* mBehaviourTree;
    VelocityFunc mVelocityFunc;
};

#endif // _AGENT_H
}}