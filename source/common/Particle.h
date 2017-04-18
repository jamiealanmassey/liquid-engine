#include "Entity.h"
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
    Particle();
    ~Particle();

    void initialise() override;
    void update() override;

    void emit(float x, float y);

    void setLifeSpan(float lifespan);
    void setColour(float r, float g, float b, float a);
    void setColour(std::array<float, 4> colour);
    const bool isAlive() const;
    const float getVelocityX() const;
    const float getVelocityY() const;
    const float getLifeTime() const;
    const float getLifeSpan() const;
    const std::array<float, 4> getColour() const;

protected:
    float                mVelocityY; ///<
    float                mVelocityX; ///< 
    float                mLifeTime;  ///< 
    float                mLifeSpan;  ///< 
    std::array<float, 4> mColour;    ///< 
};

#endif // _PARTICLE_H
}}
