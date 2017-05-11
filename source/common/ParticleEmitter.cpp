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

        mParticles.resize(mParticlesCount);
        mAtlasID = ResourceManager<data::TextureAtlas>::getResourceID("particle");
        mBlendMode = 1;

        for (uint32_t i = 0; i < mParticlesCount; i++)
            mParticles[i] = new Particle(mParticleData);
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
    }

    void ParticleEmitter::addPosition(float x, float y)
    {
        Entity::addPosition(x, y);
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

    std::vector<utilities::Vertex2*> ParticleEmitter::getVertices()
    {
        std::vector<utilities::Vertex2*> vertices;
        mVerticesCount = 0;

        for (uint32_t i = 0; i < mParticlesCount; i++)
        {
            if (mParticles[i]->isAlive())
            {
                mVerticesCount++;
                utilities::Vertex2* vertex = new utilities::Vertex2[4];
                std::array<float, 4> colours = mParticles[i]->getColour();

                float positionX = mParticles[i]->getPositionX();
                float positionY = mParticles[i]->getPositionY();

                vertex[0].setPosition(positionX, positionY);
                vertex[1].setPosition(positionX + 64.0f, positionY);
                vertex[2].setPosition(positionX + 64.0f, positionY + 64.0f);
                vertex[3].setPosition(positionX, positionY + 64.0f);

                vertex[0].setTexCoord(0.0f, 0.0f);
                vertex[1].setTexCoord(64.0f, 0.0f);
                vertex[2].setTexCoord(64.0f, 64.0f);
                vertex[3].setTexCoord(0.0f, 64.0f);

                for (uint32_t x = 0; x < 4; x++)
                {
                    vertex[x].setColour(colours[0], colours[1], colours[2], colours[3]);
                    vertices.push_back(&vertex[x]);
                }
            }
        }

        return vertices;
    }

}}
