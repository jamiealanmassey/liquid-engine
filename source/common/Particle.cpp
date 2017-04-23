#include "Particle.h"
#include "../utilities/DeltaTime.h"
#include "../utilities/Random.h"
#include "../tweener/EasingFuncs.h"

namespace liquid {
namespace common {

    Particle::Particle(const data::ParticleData& data) :
        Entity(),
        mParticleData(data)
    {
        calculateTargets();
        mLifeSpan = data.getLifeSpan()[PARTICLE_VALUE] +
            utilities::Random::instance().randomRange(
                data.getLifeSpan()[PARTICLE_VARIANCE_MIN],
                data.getLifeSpan()[PARTICLE_VARIANCE_MAX]
            );

        mLifeTime = mLifeSpan;
        mVelocityX = data.getVelocityX()[PARTICLE_VALUE];
        mVelocityY = data.getVelocityY()[PARTICLE_VALUE];
        mColour[0] = data.getColourR()[PARTICLE_VALUE];
        mColour[1] = data.getColourG()[PARTICLE_VALUE];
        mColour[2] = data.getColourB()[PARTICLE_VALUE];
        mColour[3] = data.getColourA()[PARTICLE_VALUE];

        mVelocityTweeners[0].setInitial(mVelocityX);
        mVelocityTweeners[1].setInitial(mVelocityY);
        mColourTweeners[0].setInitial(mColour[0]);
        mColourTweeners[1].setInitial(mColour[1]);
        mColourTweeners[2].setInitial(mColour[2]);
        mColourTweeners[3].setInitial(mColour[3]);

        mVelocityTweeners[0].setDuration(mLifeSpan);
        mVelocityTweeners[1].setDuration(mLifeSpan);

        tweener::EasingFunction elastic(tweener::EasingFuncs::quadratic, tweener::EasingFunction::EASINGTYPE_OUT);
        tweener::EasingFunction linear(tweener::EasingFuncs::linear);
        mVelocityTweeners[0].setEasingFunc(elastic);
        mVelocityTweeners[1].setEasingFunc(elastic);

        for (uint32_t i = 0; i < 4; i++)
        {
            mColourTweeners[i].setDuration(mLifeSpan);
            mColourTweeners[i].setEasingFunc(linear);
        }
    }

    Particle::~Particle()
    {}

    void Particle::initialise()
    {
        if (mVerticesSet)
        {
            mVerticesPtr[0]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
            mVerticesPtr[1]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
            mVerticesPtr[2]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
            mVerticesPtr[3]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
        }
    }

    void Particle::update()
    {
        if (isAlive())
        {
            float delta = utilities::DELTA;
            mLifeTime += delta;

            for (int32_t i = 0; i < 4; i++)
            {
                mColourTweeners[i].update();
                mColour[i] = mColourTweeners[i].getValue();
            }

            for (int32_t i = 0; i < 2; i++)
                mVelocityTweeners[i].update();

            mVelocityX = mVelocityTweeners[0].getValue();
            mVelocityY = mVelocityTweeners[1].getValue();

            float positionX = mPositionX + (mVelocityX * delta);
            float positionY = mPositionY + (mVelocityY * delta);
            setPosition(positionX, positionY);

            if (mVerticesSet)
            {
                mVerticesPtr[0]->setColour(mColour);
                mVerticesPtr[1]->setColour(mColour);
                mVerticesPtr[2]->setColour(mColour);
                mVerticesPtr[3]->setColour(mColour);
            }
        }
        /*else if (std::min(mLifeTime, 8000.0f))
        {
            if (mVerticesSet)
            {
                mVerticesPtr[0]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
                mVerticesPtr[1]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
                mVerticesPtr[2]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
                mVerticesPtr[3]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
            }
        }*/
    }

    void Particle::emit(float x, float y)
    {
        mLifeTime = 0.0f;
        setPosition(x, y);

        mVelocityTweeners[0].reset();
        mVelocityTweeners[1].reset();

        for (uint32_t i = 0; i < 4; i++)
            mColourTweeners[i].reset();

        if (mVerticesSet)
        {
            mVerticesPtr[0]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
            mVerticesPtr[1]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
            mVerticesPtr[2]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
            mVerticesPtr[3]->setColour(mColour[0], mColour[1], mColour[2], 0.0f);
        }

        calculateTargets();
    }

    void Particle::setLifeSpan(float lifespan)
    {
        mLifeSpan = lifespan;
    }

    void Particle::setColour(float r, float g, float b, float a)
    {
        r = std::max(std::min(r, 255.0f), 0.0f);
        g = std::max(std::min(g, 255.0f), 0.0f);
        b = std::max(std::min(b, 255.0f), 0.0f);
        a = std::max(std::min(a, 255.0f), 0.0f);
        mColour = { r,g,b,a };
    }

    void Particle::setColour(std::array<float, 4> colour)
    {
        mColour = colour;
    }

    const bool Particle::isAlive() const
    {
        return (mLifeTime < mLifeSpan);
    }

    const float Particle::getVelocityX() const
    {
        return mVelocityX;
    }

    const float Particle::getVelocityY() const
    {
        return mVelocityY;
    }

    const float Particle::getLifeTime() const
    {
        return mLifeTime;
    }

    const float Particle::getLifeSpan() const
    {
        return mLifeSpan;
    }

    const std::array<float, 4> Particle::getColour() const
    {
        return mColour;
    }

    void Particle::calculateTargets()
    {
        mVelocityTweeners[0].setTarget(
            mParticleData.getVelocityX()[PARTICLE_TARGET_VALUE] +
            liquid::utilities::Random::instance().randomRange(
                mParticleData.getVelocityX()[PARTICLE_VARIANCE_MIN],
                mParticleData.getVelocityX()[PARTICLE_VARIANCE_MAX]
            )
        );

        mVelocityTweeners[1].setTarget(
            mParticleData.getVelocityY()[PARTICLE_TARGET_VALUE] +
            liquid::utilities::Random::instance().randomRange(
                mParticleData.getVelocityY()[PARTICLE_VARIANCE_MIN],
                mParticleData.getVelocityY()[PARTICLE_VARIANCE_MAX]
            )
        );

        mColourTweeners[0].setTarget(
            mParticleData.getColourR()[PARTICLE_TARGET_VALUE] +
            utilities::Random::instance().randomRange(
                mParticleData.getColourR()[PARTICLE_VARIANCE_MIN],
                mParticleData.getColourR()[PARTICLE_VARIANCE_MAX]
            )
        );

        mColourTweeners[1].setTarget(
            mParticleData.getColourG()[PARTICLE_TARGET_VALUE] +
            utilities::Random::instance().randomRange(
                mParticleData.getColourG()[PARTICLE_VARIANCE_MIN],
                mParticleData.getColourG()[PARTICLE_VARIANCE_MAX]
            )
        );

        mColourTweeners[2].setTarget(
            mParticleData.getColourB()[PARTICLE_TARGET_VALUE] +
            utilities::Random::instance().randomRange(
                mParticleData.getColourB()[PARTICLE_VARIANCE_MIN],
                mParticleData.getColourB()[PARTICLE_VARIANCE_MAX]
            )
        );

        mColourTweeners[3].setTarget(
            mParticleData.getColourA()[PARTICLE_TARGET_VALUE] +
            utilities::Random::instance().randomRange(
                mParticleData.getColourA()[PARTICLE_VARIANCE_MIN],
                mParticleData.getColourA()[PARTICLE_VARIANCE_MAX]
            )
        );
    }

}}
