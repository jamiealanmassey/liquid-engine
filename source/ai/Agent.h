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

/**
 * \class Agent
 *
 * \ingroup AI
 * \brief The Agent is the brain of any intelligent form in the game world, stored by common::Entity objects
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class Agent
{
public:
    /// Defines a linked function for setting velocity
    typedef std::function<void(float, float)> VelocityFunc;

public:
    /// Agent Constructor
    Agent();

    /// Agent Destructor
    ~Agent();

    /// \brief Called every frame to update the Agent
    virtual void update();

    /** \brief Creates a BehaviourTree using BehaviourTreeParser with the given file
      * \param xmlBehaviourTree Location and name of the file to parse
      */
    void loadBehaviourTree(std::string xmlBehaviourTree);

    /** \brief Sets the X-Axis velocity of this Agent
      * \param velocityX Value to assign to mVelocityX
      */
    void setVelocityX(float velocityX);

    /** \brief Sets the Y-Axis velocity of this Agent
      * \param velocityY Value to assign to mVelocityY
      */
    void setVelocityY(float velocityY);

    /** \brief Sets the mass of this Agent
      * \param mass Value to assign to mMass
      */
    void setMass(float mass);

    //void setVisionDistance(float visionDist);
    //void setVisionCone(shape::Vector2& v1, shape::Vector2& v2);

    /** \brief Set the maximum velocity of the Agent as a scalar
      * \param maxVelocity Value to assign to mMaxVelocity
      */
    void setMaxVelocity(float maxVelocity);

    /** \brief Set the common::Entity that owns this Agent
      * \param entityPtr Pointer to the common::Entity in memory
      */
    void setEntityPtr(common::Entity* entityPtr);

    /** \brief Set the BehaviourTree for this Agent to process
      * \param behaviourTree Pointer to the BehaviourTree in memory
      */
    void setBehaviourTree(BehaviourTree* behaviourTree);

    /// \brief Assigns the velocity setter function
    void setVelocityFunc(VelocityFunc func);

    /// \return Gets the velocity of the Agent on the X-Axis
    const float getVelocityX() const;

    /// \return Gets the velocity of the Agent on the Y-Axis
    const float getVelocityY() const;

    /// \return Gets the mass of the Agent
    const float getMass() const;

    //const float getVisionDistance() const;
    
    /// \return Gets the maximum velocity of the Agent as a scalar
    const float getMaxVelocity() const;
    
    /// \return Velocity of the Agent with both components (x, y)
    shape::Vector2 getVelocity() const;

    /// \return Pointer to the common::Entity that owns this Agent
    common::Entity* getEntityPtr() const;

    /// \return Attached SteeringManager that steers this Agent with the computed force
    SteeringManager* getSteeringManager() const;

    /// \return Get the attached BehaviourTree to this Agent
    BehaviourTree* getBehaviourTree() const;

public:
    shape::Vector2 target;

protected:
    float            mVelocityX;       ///< Velocity of the Agent on the X-Axis
    float            mVelocityY;       ///< Velocity of the Agent on the Y-Axis
    float            mMass;            ///< Total mass of this Agent
    float            mVisionDistance;  ///< Maximum distance that this agent can see ahead
    float            mMaxVelocity;     ///< Maximum velocity that this Agent can accelerate at
    shape::Vector2   mSteeringForce;   ///< Current steering force to apply to the Agent every frame
    shape::Vector2   mVisionCone[2];   ///< Where the Agent can see
    common::Entity*  mEntityPtr;       ///< Pointer to the common::Entity that owns this Agent
    SteeringManager* mSteeringManager; ///< SteeringManager to calculate and apply steering behaviours
    BehaviourTree*   mBehaviourTree;   ///< Pointer to parsed/set BehaviourTree to process every frame
    VelocityFunc     mVelocityFunc;    ///< Velocity function to assign when velocity is set
};

#endif // _AGENT_H
}}
