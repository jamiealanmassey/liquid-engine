#include "LineSegment.h"
#include "Rectangle.h"
#include "Circle.h"

namespace liquid {
namespace shape {

    LineSegment::LineSegment(std::array<float, 4> segment) :
        IShape(2)
    {
    setLine(segment);
    }

    LineSegment::LineSegment(float x1, float y1, float x2, float y2) :
        IShape(2)
    {
        setLine(x1, y1, x2, y2);
    }

    LineSegment::~LineSegment()
    {
    }

    void LineSegment::setLine(std::array<float, 4> segment)
    {
        mLineSegment = segment;
        mDirection.setDirectionX(segment[2] - segment[0]);
        mDirection.setDirectionY(segment[3] - segment[1]);
    }

    void LineSegment::setLine(float x1, float y1, float x2, float y2)
    {
        mLineSegment = { x1, y1, x2, y2 };
        mDirection.setDirectionX(x2 - x1);
        mDirection.setDirectionY(y2 - y1);
    }

    bool LineSegment::intersection(Rectangle& rectangle)
    {
        return rectangle.intersection(*this);
    }

    bool LineSegment::intersection(Circle& circle)
    {
        return circle.intersection(*this);
    }

    bool LineSegment::intersection(LineSegment& line)
    {
        return false;
    }

    bool LineSegment::intersection(std::array<float, 2> point)
    {
        return false;
    }

    const std::array<float, 4> LineSegment::getLineSegment() const
    {
        return mLineSegment;
    }

    const Vector2& LineSegment::getDirection() const
    {
        return mDirection;
    }

}}
