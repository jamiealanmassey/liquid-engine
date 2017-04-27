#include "Light.h"

namespace liquid {
namespace graphics {

    Light::Light()
    {

    }

    Light::Light(std::array<float, 2> position, std::array<float, 4> colour, float intensity, float radius)
    {
        mLightPosition = position;
        mLightColour = colour;
        mLightIntensity = intensity;
        mLightRadius = radius;
        mPointCount = 0;

        generate(32);
    }

    Light::~Light()
    {}

    void Light::update()
    {
    }

    void Light::generate(uint32_t pointCount)
    {
        mPointCount = pointCount + 2;
        mLightGeometry.clear();
        mLightGeometry.resize(mPointCount);

        mLightGeometry[0].setPosition(0.0f, 0.0f);
        mLightGeometry[0].setColour(mLightColour[0], mLightColour[1], 
                                    mLightColour[2], mLightIntensity * 255.0f);

        for (uint32_t i = 1; i < (mPointCount - 1); i++)
        {
            float angle = (float)(PI * 2.0) * ((float)i / (float)(mPointCount - 2));
            float positionX = mLightRadius * std::cos(angle);
            float positionY = mLightRadius * std::sin(angle);

            mLightGeometry[i].setPosition(positionX, positionY);
            mLightGeometry[i].setColour(0.f, 0.f, 0.f, 0.f);
        }

        mLightGeometry[mPointCount - 1] = mLightGeometry[1];
    }

    void Light::setLightPosition(std::array<float, 2> position)
    {
        mLightPosition = position;
        generate(mPointCount);
    }

    void Light::setLightColour(std::array<float, 4> colour)
    {
        mLightColour = colour;
    }

    void Light::setLightIntensity(float intensity)
    {
        mLightIntensity = intensity;
    }

    void Light::setLightRadius(float radius)
    {
        mLightRadius = radius;
    }

    const std::vector<utilities::Vertex2> Light::getLightGeometry() const
    {
        return mLightGeometry;
    }

    const std::array<float, 2> Light::getLightPosition() const
    {
        return mLightPosition;
    }

    const std::array<float, 4> Light::getLightColour() const
    {
        return mLightColour;
    }

    const float Light::getLightIntensity() const
    {
        return mLightIntensity;
    }

    const float Light::getLightRadius() const
    {
        return mLightRadius;
    }

    const uint32_t Light::getPointCount() const
    {
        return mPointCount;
    }

}}
