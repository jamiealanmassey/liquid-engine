#include "Entity.h"
#include "../data/ParticleData.h"
#include "../tweener/Tweener.h"
#include <array>

namespace liquid { namespace common {
#ifndef _PARTICLE_H
#define _PARTICLE_H

/**
 * \class Particle
 *
 * \ingroup Common
 * \brief Defines a single Particle in 2D-Space
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 18/04/2017
 *
 */

class Particle : public Entity
{
public:
    /** \brief Particle Constructor
      * \param data Particle Data to construct from
      */
    Particle(const data::ParticleData& data);

    /// Particle Destructor
    ~Particle();

    /// Called when Particle is first initialised
    void initialise() override;

    /** \brief Updates the Particle
      *
      * Not only does this update the position of the Particle but the function
      * is also responsible for making sure all the running Tweeners are also 
      * updated on every step. Additionality if some Vertices are set for this
      * particle then they will be updated also.
      */
    void update() override;

    /** \brief Emit the Particle
      * \param x X-Coordinate to emit from
      * \param y Y-Coordinate to emit from
      *
      * Resets and emits the particle from the given position. The tweener::Tweener
      * objects used by this Particle are also reset to their initial state
      */
    void emit(float x, float y);

    /** \brief Set the lifespan of this Particle
      * \param lifespan Variable to be set
      */
    void setLifeSpan(float lifespan);

    /** \brief Set the colour of this Particle
      * \param r R colour of the Particle (0 - 255)
      * \param g G colour of the Particle (0 - 255)
      * \param b B colour of the Particle (0 - 255)
      * \param a A colour of the Particle (0 - 255)
      */
    void setColour(float r, float g, float b, float a);

    /** \brief Set the colour of this Particle
      * \param colour Array representation of Particle colour (RGBA)
      */
    void setColour(std::array<float, 4> colour);

    /// \return True if the Particle is still alive, otherwise False
    const bool isAlive() const;

    /// \return Gets the X-Axis velocity of this Particle
    const float getVelocityX() const;

    /// \return Gets the Y-Axis velocity of this Particle
    const float getVelocityY() const;

    /// \return Gets the life time of this Particle
    const float getLifeTime() const;

    /// \return Gets the total life span of this Particle
    const float getLifeSpan() const;

    /// \return Gets the colour of this particle as a std::array
    const std::array<float, 4> getColour() const;

protected:
    /// \brief Calculates new target tweener::Tweener values
    void calculateTargets();

protected:
    float                mVelocityX; ///< Velocity to apply on the X-Axis
    float                mVelocityY; ///< Velocity to apply on the Y-Axis
    float                mLifeTime;  ///< Total lifetime of the Particle so far
    float                mLifeSpan;  ///< Maximum lifetime of the Particle
    std::array<float, 4> mColour;    ///< Particle's current colour

protected:
    tweener::Tweener mVelocityTweeners[2]; ///< Tweeners for velocity (x,y) == (0,1)
    tweener::Tweener mColourTweeners[4];   ///< Tweeners for colour (r,g,b,a) == (0,1,2,3)

private:
    const data::ParticleData& mParticleData; ///< Copy of particle data
};

#endif // _PARTICLE_H
}}
