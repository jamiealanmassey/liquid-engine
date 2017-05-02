#include "IShape.h"
#include <array>

namespace liquid { namespace shape {
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

class Rectangle : public IShape
{
public:
    Rectangle();
    ~Rectangle();

    void setRectangle(std::array<float, 4> rectangle);
    void setRectangle(float x, float y, float w, float h);

    virtual bool intersection(Rectangle& rectangle) override;
    virtual bool intersection(Circle& circle) override;
    virtual bool intersection(LineSegment& line) override;
    virtual bool intersection(std::array<float, 2> point) override;

    const std::array<float, 4> getRectangle() const;

protected:
    std::array<float, 4> mRectangle;
};

#endif // _RECTANGLE_H
}}
