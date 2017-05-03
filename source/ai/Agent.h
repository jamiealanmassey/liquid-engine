#include "../shapes/Vector2.h"
#include "../shapes/Rectangle.h"

namespace liquid { namespace common { class Entity; } }

namespace liquid { namespace ai {
#ifndef _AGENT_H
#define _AGENT_H

class Agent
{
public:
    Agent();
    ~Agent();

    virtual void update();

    // TODO: STEERING BEHAVIOURS


    void setVelocityX(float* velocityX);
    void setVelocityY(float* velocityY);

    void setVisionDistance(float visionDist);
    void setVisionCone(shape::Vector2& v1, shape::Vector2& v2);
    void setMaxVelocity(float maxVelocity);
    void setTargetAgent(Agent* targetAgent);
    void setEntityPtr(common::Entity* entityPtr);

    const float getVelocityX() const;
    const float getVelocityY() const;
    const float getVisionDistance() const;
    const float getMaxVelocity() const;
    
    Agent* getTargetAgent() const;
    shape::Vector2& getVelocity() const;
    common::Entity* getEntityPtr() const;

protected:
    float* mVelocityX;
    float* mVelocityY;
    float mVisionDistance;
    float mMaxVelocity;
    Agent* mTargetAgent;
    shape::Vector2 mVisionCone[2];
    common::Entity* mEntityPtr;
};

#endif // _AGENT_H
}}
