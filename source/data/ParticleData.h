#include "../parser/ParserConfig.h"
#include <array>

namespace liquid { namespace data {
#ifndef _PARTICLEDATA_H
#define _PARTICLEDATA_H

#define PARTICLE_VALUE 0
#define PARTICLE_VARIANCE_MIN 1
#define PARTICLE_VARIANCE_MAX 2
#define PARTICLE_TARGET_VALUE 3

/**
 * \class ParticleData
 *
 * \ingroup Data
 * \brief Defines a complex data-structure that describes a common::Particle
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 20/04/2017
 *
 */

class ParticleData
{
public:
    /// Array of floats defining Particle data
    typedef std::array<float, 4> ParticleNode;

public:
    /** \brief ParticleData Constructor
      * \param parser Parser to gather data for this structure 
      */
    ParticleData(parser::ParserConfig parser);

    /// ParticleData Destructor
    ~ParticleData();

    /// \brief Gets the X-Axis Velocity as a ParticleNode
    const ParticleNode getVelocityX() const;

    /// \brief Gets the Y-Axis Velocity as a ParticleNode
    const ParticleNode getVelocityY() const;

    /// \brief Gets the red colour channel as a ParticleNode
    const ParticleNode getColourR() const;

    /// \brief Gets the green colour channel as a ParticleNode
    const ParticleNode getColourG() const;

    /// \brief Gets the blue colour channel as a ParticleNode
    const ParticleNode getColourB() const;

    /// \brief Gets the alpha channel as a ParticleNode
    const ParticleNode getColourA() const;

    /// \brief Gets the size on the X-Axis as a ParticleNode
    const ParticleNode getSizeX() const;

    /// \brief Gets the size on the Y-Axis as a ParticleNode
    const ParticleNode getSizeY() const;

    /// \brief Gets the life span as a ParticleNode
    const ParticleNode getLifeSpan() const;

    /// \brief Gets the name of the texture to use
    const std::string getTexture() const;

    /// \brief Describes the easing function using a name
    const std::string getEasingFunctionName() const;

protected:
    ParticleNode mVelocityX;     ///< Velocity on the X-Axis
    ParticleNode mVelocityY;     ///< Velocity on the Y-Axis
    ParticleNode mColourR;       ///< Colour Red
    ParticleNode mColourG;       ///< Colour Green
    ParticleNode mColourB;       ///< Colour Blue
    ParticleNode mColourA;       ///< Colour Alpha
    ParticleNode mSizeX;         ///< Size on the X-Axis
    ParticleNode mSizeY;         ///< Size on the Y-Axis
    ParticleNode mLifeSpan;      ///< The Life Span 
    std::string  mTexture;       ///< Name of the texture to use
    std::string  mEaseFunction;  ///< Name of the easing function

protected:
    parser::ParserConfig mParser; ///< Parser
};

#endif // _PARTICLEDATA_H
}}
