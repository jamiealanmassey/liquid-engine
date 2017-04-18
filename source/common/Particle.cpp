#include "Particle.h"
#include "../utilities/DeltaTime.h"

namespace liquid {
namespace common {

    Particle::Particle()
    {}

    Particle::~Particle()
    {}

    void Particle::initialise()
    {}

    void Particle::update()
    {
        if (isAlive())
        {
            float delta = utilities::DELTA;
            float ratio = mLifeTime / mLifeSpan;
            mLifeTime += delta;

            float positionX = mPositionX + (mVelocityX * delta);
            float positionY = mPositionY + (mVelocityY * delta);
            setPosition(positionX, positionY);

            // TODO: Lerp over other values
        }
    }

    void Particle::emit(float x, float y)
    {
        mLifeTime = 0.0f;
        setPosition(x, y);

        // TODO: Reset colour, size, velocity etc.
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
        return (mLifeTime <= mLifeSpan);
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

}}
