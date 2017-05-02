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
        std::array<float, 4> targetLine = line.getLineSegment();
        std::array<float, 2> targetA = { targetLine[0], targetLine[1] };
        std::array<float, 2> targetB = { targetLine[2], targetLine[3] };

        std::array<float, 2> lineA = { mLineSegment[0], mLineSegment[1] };
        std::array<float, 2> lineB = { mLineSegment[2], mLineSegment[3] };

        float d = ((targetB[1] - targetA[1]) * (lineB[0] - lineA[0])) -
                  ((targetB[0] - targetA[0]) * (lineB[1] - lineA[1]));

        if (d == 0.0f)
            return false;

        float ma = (((targetB[0] - targetA[0]) * (lineA[1] - targetA[1])) -
                    ((targetB[1] - targetA[1]) * (lineA[0] - targetA[0]))) / d;

        float mb = (((lineB[0] - lineA[0]) * (lineA[1] - targetA[1])) -
                    ((lineB[1] - lineA[1]) * (lineA[0] - targetA[0]))) / d;

        return ((ma < 0.0f && ma > 1.0f) && (mb < 0.0f && mb > 1.0f));
    }

    bool LineSegment::intersection(std::array<float, 2> point)
    {
        // TODO: line-point intersection test
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
