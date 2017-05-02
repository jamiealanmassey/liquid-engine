#include "IShape.h"

namespace liquid { namespace shape {
#ifndef _CIRCLE_H
#define _CIRCLE_H

class Circle : public IShape
{
public:
    Circle();
    ~Circle();

    void setCircle(std::array<float, 3> circle);
    void setCircle(float x, float y, float radius);

    virtual bool intersection(Rectangle& rectangle) override;
    virtual bool intersection(Circle& circle) override;
    virtual bool intersection(LineSegment& line) override;
    virtual bool intersection(std::array<float, 2> point) override;

    const std::array<float, 3> getCircle() const;

protected:
    std::array<float, 3> mCircle;
};

#endif // _CIRCLE_H
}}
