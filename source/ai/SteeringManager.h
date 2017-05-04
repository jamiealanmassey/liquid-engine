#include "../shapes/Vector2.h"

namespace liquid { namespace ai {
#ifndef _STEERINGMANAGER_H
#define _STEERINGMANAGER_H

/**
 * \class SteeringManager
 *
 * \ingroup AI
 * \brief Calculates a force by adding multiple different steering behaviours together
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class Agent;
class SteeringManager
{
public:
    /** \brief SteeringManager Constructor
      * \param parentAgent Pointer to the parent Agent to calculate for
      */
    SteeringManager(Agent* parentAgent);
    
    /// SteeringManager Destructor
    ~SteeringManager();

    /// \brief Called every frame, resets forces and calculates
    void update();

    /// \brief Resets the SteeringManager variables
    void reset();

    /// \brief Wanders around in various directions
    shape::Vector2 wander();

    /** \brief Seeks the given target and creates a direction Vector2 towards it
      * \param target Point to seek in 2D-space (x, y)
      */
    shape::Vector2 seek(shape::Vector2& target, float slowingRadius = 0.f);

    /** \brief Creates a Vector2 away from the target and calls seek with it
      * \param target Point to flee from in 2D-space (x, y)
      */
    shape::Vector2 flee(shape::Vector2& target);

    /** \brief Evades the given Agent
      * \param target Target Agent to evade from
      */
    shape::Vector2 evade(Agent* target);

    /** \brief Pursue towards given Agent by predicting its movement direction
      * \param target Target Agent to pursue to
      */
    shape::Vector2 pursue(Agent* target);

    /// \return Gets a pointer to the parent Agent object
    Agent* getParentAgent() const;

    /// \return Gets the current calculated steering force
    shape::Vector2 getSteeringForce() const;

    /// \return Gets the weighted steering velocity
    shape::Vector2 getSteeringVelocity() const;

protected:
    /** \brief Internal function to retrieve an Agent's position
      * \param agent Pointer to the Agent to get the position of
      * \return Extracted position as a Vector2
      */
    shape::Vector2 getPosition(Agent* agent);

    /** \brief Internal function calculate the new angle of a given Vector2
      * \param v Current Vector2 to be transformed
      * \return Calculated Vector2 with given angle
      */
    shape::Vector2 calculateAngle(shape::Vector2& v, float angle);

    /** \brief Internal function to truncate the vector given the maximum force
      * \param agent Pointer to the Agent to get the position of
      * \param v Current Vector2 to be transformed
      * \return Calculated Vector2 with given maxForce
      */
    shape::Vector2 truncate(shape::Vector2& steering, float maxForce);

protected:
    float          mWanderAngle;      ///< Angle to wander about
    Agent*         mParentAgent;      ///< Pointer to the Agent that owns this SteeringManager
    shape::Vector2 mSteeringForce;    ///< Calculated steering force this frame
    shape::Vector2 mSteeringVelocity; ///< Calculated steering velocity (truncated) this frame

protected:
    const float mCircleDistance; ///< Circle distance for wandering
    const float mCircleRadius;   ///< Circle radius for wandering
    const float mAngleChange;    ///< Calculated next angle change for wandering
    const float mMaxForce;       ///< Maximum force of the steering force
};

#endif // _STEERINGMANAGER_H
}}
