#include "Entity.h"
#include "Particle.h"
#include "../data/ParticleData.h"
#include "../graphics/RenderableBatch.h"

namespace liquid { namespace common {
#ifndef _PARTICLEEMITTER_H
#define _PARTICLEEMITTER_H

/**
 * \class ParticleEmitter
 *
 * \ingroup Common
 * \brief Subsystem that manages a Particle System for simulating
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 18/04/2017
 *
 */

class ParticleEmitter : public Entity
{
public:
    enum eEmitterType
    {
        EMITTERTYPE_UNDEFINED = 0,
        EMITTERTYPE_DIRECTIONAL = 1,
        EMITTERTYPE_CIRCULAR = 2,
    };

public:
    ParticleEmitter(data::ParticleData& particleData, graphics::RenderableBatch* batch, uint32_t count);
    ~ParticleEmitter();

    virtual void update() override;
    virtual void updatePost() override;

    void setBirthRate(float rate);
    void setType(eEmitterType type);

    const uint32_t getParticlesCount() const;
    const float getBirthRate() const;
    const float getBirthAccumulator() const;
    const eEmitterType getType() const;

    const std::vector<Particle*>& getParticles();

protected:
    uint32_t               mParticlesCount;
    float                  mBirthRate;
    float                  mBirthAccumulator; 
    eEmitterType           mType; ///< 
    std::vector<Particle*> mParticles; ///< 

protected:
    graphics::RenderableBatch* mRenderableBatch; ///< 
    data::ParticleData&        mParticleData;    ///< 
};

#endif // _PARTICLEEMITTER_H
}}
