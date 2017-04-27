#include "../utilities/Vertex2.h"
#include <vector>
#include <array>

namespace liquid { namespace graphics {
#ifndef _LIGHT_H
#define _LIGHT_H

#define PI 3.14159265359

class Light
{
public:
    Light();
    Light(std::array<float, 2> position, std::array<float, 4> colour, float intensity, float radius);
    ~Light();

    virtual void update();
    virtual void generate(uint32_t pointCount);

    void setLightPosition(std::array<float, 2> position);
    void setLightColour(std::array<float, 4> colour);
    void setLightIntensity(float intensity);
    void setLightRadius(float radius);

    const std::vector<utilities::Vertex2> getLightGeometry() const;
    const std::array<float, 2> getLightPosition() const;
    const std::array<float, 4> getLightColour() const;
    const float getLightIntensity() const;
    const float getLightRadius() const;
    const uint32_t getPointCount() const;

protected:
    std::vector<utilities::Vertex2> mLightGeometry;
    std::array<float, 2> mLightPosition;
    std::array<float, 4> mLightColour;
    float mLightIntensity;
    float mLightRadius;
    uint32_t mPointCount;
};

#endif // _LIGHT_H
}}
