#include "Vertex2.h"

namespace liquid {
namespace utilities {

    Vertex2::Vertex2()
    {
        mPosition = { 0.0f, 0.0f };
        mColour = { 255.0f, 255.0f, 255.0f, 255.0f };
        mTexCoord = { 0.0f, 0.0f };
    }

    Vertex2::Vertex2(std::array<float, 2> position, std::array<float, 4> colour, std::array<float, 2> texCoord)
    {
        mPosition = position;
        mColour = colour;
        mTexCoord = texCoord;
    }

    Vertex2::~Vertex2()
    {}

    void Vertex2::setPosition(std::array<float, 2> position)
    {
        mPosition = position;
        mChanged = true;
    }

    void Vertex2::setPosition(float x, float y)
    {
        mPosition = { x, y };
        mChanged = true;
    }

    void Vertex2::setColour(std::array<float, 4> colour)
    {
        mColour = colour;
        mChanged = true;
    }

    void Vertex2::setColour(float r, float g, float b, float a)
    {
        r = std::max(std::min(r, 255.0f), 0.0f);
        g = std::max(std::min(g, 255.0f), 0.0f);
        b = std::max(std::min(b, 255.0f), 0.0f);
        a = std::max(std::min(a, 255.0f), 0.0f);

        mColour = { r, g, b, a };
        mChanged = true;
    }

    void Vertex2::setTexCoord(std::array<float, 2> texCoord)
    {
        mTexCoord = texCoord;
        mChanged = true;
    }

    void Vertex2::setTexCoord(float x, float y)
    {
        mTexCoord = { x, y };
        mChanged = true;
    }

    void Vertex2::resetChanged()
    {
        mChanged = false;
    }

    const std::array<float, 2> Vertex2::getPosition() const
    {
        return mPosition;
    }

    const std::array<float, 4> Vertex2::getColour() const
    {
        return mColour;
    }

    const std::array<float, 2> Vertex2::getTexCoord() const
    {
        return mTexCoord;
    }

    const bool Vertex2::hasChanged() const
    {
        return mChanged;
    }

}}
