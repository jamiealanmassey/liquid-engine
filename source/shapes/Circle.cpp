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

        float distanceX = targetLine[2] - targetLine[0];
        float distanceY = targetLine[3] - targetLine[1];

        float circleDistanceX = distanceX * (targetLine[0] - mCircle[0]);
        float circleDistanceY = distanceY * (targetLine[1] - mCircle[1]);
        
        float circleXSq = std::pow(targetLine[0] - mCircle[0], 2);
        float circleYSq = std::pow(targetLine[1] - mCircle[1], 2);

        float a = (distanceX * distanceX) + (distanceY * distanceY);
        float b = 2.0f * (circleDistanceX + circleDistanceY);
        float c = (circleXSq + circleYSq) - std::pow(mCircle[2], 2);

        float det = (b*b) - 4.0f * a*c;
        return !((a <= 0.0000001f) || det < 0.0f);
    }

    bool Circle::intersection(std::array<float, 2> point)
    {
        float distanceX = std::fabsf(mCircle[0] - point[0]);
        float distanceY = std::fabsf(mCircle[1] - point[1]);
        float distanceSq = std::sqrt(std::pow(distanceX, 2) + std::pow(distanceY, 2));

        return (distanceSq <= mCircle[2]);
    }

    const std::array<float, 3> Circle::getCircle() const
    {
        return mCircle;
    }

}}
