#include "ConfigurationParser.h"
#include <array>

namespace liquid { namespace data {
#ifndef _PARTICLEDATA_H
#define _PARTICLEDATA_H

#define PARTICLE_VALUE 0
#define PARTICLE_VARIANCE_MIN 1
#define PARTICLE_VARIANCE_MAX 2
#define PARTICLE_TARGET_VALUE 3

class ParticleData
{
public:
    typedef std::array<float, 4> ParticleNode;

public:
    ParticleData(ConfigurationParser parser);
    ~ParticleData();

    const ParticleNode getVelocityX() const;
    const ParticleNode getVelocityY() const;
    const ParticleNode getColourR() const;
    const ParticleNode getColourG() const;
    const ParticleNode getColourB() const;
    const ParticleNode getColourA() const;
    const ParticleNode getSizeX() const;
    const ParticleNode getSizeY() const;
    const ParticleNode getLifeSpan() const;
    const std::string getTexture() const;
    const std::string getEasingFunctionName() const;

protected:
    ParticleNode mVelocityX;     ///< 
    ParticleNode mVelocityY;     ///< 
    ParticleNode mColourR;       ///< 
    ParticleNode mColourG;       ///< 
    ParticleNode mColourB;       ///< 
    ParticleNode mColourA;       ///< 
    ParticleNode mSizeX;         ///< 
    ParticleNode mSizeY;         ///< 
    ParticleNode mLifeSpan;      ///< 
    std::string  mTexture;       ///< 
    std::string  mEaseFunction;  ///< 

protected:
    ConfigurationParser mParser; ///< 
};

#endif // _PARTICLEDATA_H
}}
