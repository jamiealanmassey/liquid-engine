#include "ParticleEmitter.h"
#include "../utilities/DeltaTime.h"
#include "../data/TextureAtlas.h"
#include "ResourceManager.h"

namespace liquid {
namespace common {

    ParticleEmitter::ParticleEmitter(data::ParticleData& particleData, Layer* layerPtr, uint32_t count) :
        Entity(),
        mParticleData(particleData)
    {
        mParticles.resize(count);
        mParticlesCount = count;
        mParticlesBirth = count;
        mBirthRate = 10.0f;
        mBirthAccumulator = 0.0f;
        mRepeat = true;

        mAtlasID = ResourceManager<data::TextureAtlas>::getResourceID("particle");
        mBlendMode = 1;

        for (uint32_t i = 0; i < mParticlesCount; i++)
        {
            mParticles[i] = new Particle(mParticleData);
            mParticles[i]->setPosition(mPositionX, mPositionY);
            mParticles[i]->mAtlasID = mAtlasID;
            mParticles[i]->mBlendMode = mBlendMode;
            mParticles[i]->setSize(64.0f, 64.0f);
            mParticles[i]->setTexCoords(0.f, 0.f, 64.f, 64.f);
            layerPtr->insertEntity(mParticles[i]);
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
