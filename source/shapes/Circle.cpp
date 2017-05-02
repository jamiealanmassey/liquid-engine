#include "Circle.h"
#include "Rectangle.h"
#include "LineSegment.h"

namespace liquid {
namespace shape {

    Circle::Circle() :
        IShape(1)
    {
    }

    Circle::~Circle()
    {
    }

    void Circle::setCircle(std::array<float, 3> circle)
    {
        mCircle = circle;
    }

    void Circle::setCircle(float x, float y, float radius)
    {
        mCircle = { x,y,radius };
    }

    bool Circle::intersection(Rectangle& rectangle)
    {
        return rectangle.intersection(*this);
    }

    bool Circle::intersection(Circle& circle)
    {
        std::array<float, 3> targetCircle = circle.getCircle();

        float distanceX = std::fabsf(targetCircle[0] - mCircle[0]);
        float distanceY = std::fabsf(targetCircle[1] - mCircle[1]);

        float distanceR0 = std::pow(std::fabsf(targetCircle[2] - mCircle[2]), 2);
        float distanceR1 = std::pow(std::fabsf(targetCircle[2] + mCircle[2]), 2);
        float distanceSq = std::pow(distanceX, 2) + std::pow(distanceY, 2);

        return (distanceR0 <= distanceSq && distanceSq <= distanceR1);
    }

    bool Circle::intersection(LineSegment& line)
    {
        std::array<float, 4> targetLine = line.getLineSegment();
        Vector2 lineDirection = line.getDirection();

        Vector2 distance0(mCircle[0] - targetLine[0], mCircle[1] - targetLine[1]);
        Vector2 distance1(mCircle[0] - targetLine[2], mCircle[1] - targetLine[3]);
        
        float lineNormal = lineDirection.projection(lineDirection.lineNormal());
        float lineProjX = lineDirection.projection(Vector2(1, 0));

        Vector2 lineX = VECTOR2X;
        lineX.setMagnitude(lineProjX);

        float dotProd0 = lineX.dotProduct(distance0);
        float dotProd1 = lineX.dotProduct(distance1);
        bool normalCheck = (std::fabsf(lineNormal) <= mCircle[2]);

        return (normalCheck && dotProd0 > 0.f && dotProd1 < 0);
    }

    bool Circle::intersection(std::array<float, 2> point)
    {
        float distanceX = std::fabsf(mCircle[0] - point[0]);
        float distanceY = std::fabsf(mCircle[1] - point[1]);
        float distanceSq = std::pow(distanceX, 2) + std::pow(distanceY, 2);

        return (distanceSq <= std::pow(mCircle[2], 2));
    }

    const std::array<float, 3> Circle::getCircle() const
    {
        return mCircle;
    }

}}
