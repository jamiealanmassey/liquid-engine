#include "ParticleEmitter.h"
#include "../utilities/DeltaTime.h"

namespace liquid {
namespace common {

    ParticleEmitter::ParticleEmitter(data::ParticleData& particleData, graphics::RenderableBatch* batch, uint32_t count) :
        Entity(),
        mParticleData(particleData)
    {
        mParticlesCount = count;
        mBirthRate = 100.0f;
        mBirthAccumulator = 0.0f;

        for (uint32_t i = 0; i < mParticlesCount; i++)
        {
            mParticles.push_back(new Particle(mParticleData));
            mParticles.back()->setVerticesPtr(batch->nextVertices());
        }
    }

    ParticleEmitter::~ParticleEmitter()
    {
        for (auto p : mParticles)
            delete p;

        mParticles.clear();
    }

    void ParticleEmitter::update()
    {
        mBirthAccumulator += utilities::DELTA;

        for (uint32_t i = 0; i < mParticlesCount; i++)
        {
            if (mParticles[i]->isAlive())
                mParticles[i]->update();
            else
            {
                if (mBirthAccumulator >= mBirthRate)
                {
                    mParticles[i]->emit(mPositionX, mPositionY);
                    mBirthAccumulator -= mBirthRate;
                }
            }
        }
    }

    void ParticleEmitter::updatePost()
    {

    }

    void ParticleEmitter::setBirthRate(float rate)
    {
        mBirthRate = std::fabsf(rate);
    }

    void ParticleEmitter::setType(eEmitterType type)
    {
        mType = type;
    }

    const uint32_t ParticleEmitter::getParticlesCount() const
    {
        return mParticlesCount;
    }

    const float ParticleEmitter::getBirthRate() const
    {
        return mBirthRate;
    }

    const float ParticleEmitter::getBirthAccumulator() const
    {
        return mBirthAccumulator;
    }

    const ParticleEmitter::eEmitterType ParticleEmitter::getType() const
    {
        return mType;
    }

    const std::vector<Particle*>& ParticleEmitter::getParticles()
    {
        return mParticles;
    }

}}
