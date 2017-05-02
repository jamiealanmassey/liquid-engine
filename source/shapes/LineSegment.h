#include "IShape.h"
#include "Vector2.h"

namespace liquid { namespace shape {
#ifndef _LINESEGMENT_H
#define _LINESEGMENT_H

class LineSegment : public IShape
{
public:
    LineSegment(std::array<float, 4> segment);
    LineSegment(float x1, float y1, float x2, float y2);
    ~LineSegment();

    virtual void setLine(std::array<float, 4> segment);
    virtual void setLine(float x1, float y1, float x2, float y2);

    virtual bool intersection(Rectangle& rectangle) override;
    virtual bool intersection(Circle& circle) override;
    virtual bool intersection(LineSegment& line) override;
    virtual bool intersection(std::array<float, 2> point) override;

    const std::array<float, 4> getLineSegment() const;
    const Vector2& getDirection() const;

protected:
    std::array<float, 4> mLineSegment;
    Vector2              mDirection;
};

#endif // _LINESEGMENT_H
}}
