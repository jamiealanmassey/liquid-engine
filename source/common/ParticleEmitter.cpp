#include "ParticleEmitter.h"
#include "../utilities/DeltaTime.h"

namespace liquid {
namespace common {

    ParticleEmitter::ParticleEmitter(data::ParticleData& particleData, graphics::RenderableBatch* batch, uint32_t count) :
        Entity(),
        mParticleData(particleData)
    {
        mParticles.resize(count);
        mParticlesCount = count;
        mParticlesBirth = count;
        mBirthRate = 100.0f;
        mBirthAccumulator = 0.0f;
        mRepeat = true;

        for (uint32_t i = 0; i < mParticlesCount; i++)
        {
            mParticles[i] = new Particle(mParticleData);
            mParticles[i]->setVerticesPtr(batch->nextVertices());
            mParticles[i]->initialise();
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
        if (mRepeat == true || (mRepeat == false && mParticlesBirth > 0))
            mBirthAccumulator += utilities::DELTA;

        for (uint32_t i = 0; i < mParticlesCount; i++)
        {
            if (mParticles[i]->isAlive())
                mParticles[i]->update();
            else
            {
                if (mRepeat == false && mParticlesBirth == 0)
                    continue;

                if (mBirthAccumulator >= mBirthRate)
                {
                    mParticles[i]->emit(mPositionX, mPositionY);
                    mBirthAccumulator -= mBirthRate;

                    if (mRepeat == false)
                        mParticlesBirth--;
                }
            }
        }
    }

    void ParticleEmitter::updatePost()
    {

    }

    void ParticleEmitter::setPosition(float x, float y)
    {
        Entity::setPosition(x, y);

        for (uint32_t i = 0; i < mParticlesCount; i++)
            mParticles[i]->setPosition(x, y);
    }

    void ParticleEmitter::addPosition(float x, float y)
    {
        Entity::addPosition(x, y);

        for (uint32_t i = 0; i < mParticlesCount; i++)
            mParticles[i]->addPosition(x, y);
    }

    void ParticleEmitter::emit()
    {
        if (mParticlesBirth == 0 && mRepeat == false)
            mParticlesBirth += mParticlesCount;
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
