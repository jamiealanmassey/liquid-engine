#include <cstdint>
#include <array>

namespace liquid { namespace shape {
#ifndef _ISHAPE_H
#define _ISHAPE_H

class Rectangle;
class Circle;
class LineSegment;
class IShape
{
public:
    IShape(uint32_t pointCount)
    {
        mPointCount = pointCount;
    }
    
    ~IShape()
    {
    }

    const uint32_t getPointCount() const
    {
        return mPointCount;
    }

    virtual bool intersection(Rectangle& rectangle) = 0;
    virtual bool intersection(Circle& circle) = 0;
    virtual bool intersection(LineSegment& line) = 0;
    virtual bool intersection(std::array<float, 2> point) = 0;

protected:
    uint32_t mPointCount;
};

#endif // _ISHAPE_H
}}
