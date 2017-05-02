#include "Rectangle.h"
#include "Circle.h"
#include "LineSegment.h"

namespace liquid {
namespace shape {

    Rectangle::Rectangle() :
        IShape(4)
    {
    }

    Rectangle::~Rectangle()
    {
    }

    void Rectangle::setRectangle(std::array<float, 4> rectangle)
    {
        mRectangle = rectangle;
    }

    void Rectangle::setRectangle(float x, float y, float w, float h)
    {
        mRectangle = { x,y,w,h };
    }

    bool Rectangle::intersection(Rectangle& rectangle)
    {
        std::array<float, 4> targetRectangle = rectangle.getRectangle();

        float distanceX = std::fabsf(targetRectangle[0] - mRectangle[0]);
        float distanceY = std::fabsf(targetRectangle[1] - mRectangle[1]);

        float sizeX = (targetRectangle[2] / 2.0f) + (mRectangle[2] / 2.0f);
        float sizeY = (targetRectangle[3] / 2.0f) + (mRectangle[3] / 2.0f);

        return (sizeX <= distanceX && sizeY <= distanceY);
    }

    bool Rectangle::intersection(Circle& circle)
    {
        std::array<float, 3> targetCircle = circle.getCircle();

        float distanceX = std::fabsf(targetCircle[0] - mRectangle[0]);
        float distanceY = std::fabsf(targetCircle[1] - mRectangle[1]);
        float halfSizeX = mRectangle[2] / 2.0f;
        float halfSizeY = mRectangle[3] / 2.0f;

        if (distanceX > (halfSizeX + targetCircle[2]))
            return false;
        
        if (distanceY > (halfSizeY + targetCircle[2]))
            return false;

        float distanceSq = std::pow(distanceX - halfSizeX, 2) + 
                           std::pow(distanceY - halfSizeY, 2);

        return (distanceSq <= (std::pow(targetCircle[2], 2)));
    }

    bool Rectangle::intersection(LineSegment& line)
    {
        std::array<float, 4> targetLine = line.getLineSegment();

        float halfSizeX = mRectangle[2] / 2.0f;
        float halfSizeY = mRectangle[3] / 2.0f;

        float slope = (targetLine[1] - targetLine[3]) / 
                      (targetLine[0] - targetLine[2]);

        return ((-halfSizeY <= slope * halfSizeX <= halfSizeY) ||
                (-halfSizeX <= halfSizeY / slope <= halfSizeX));
    }

    bool Rectangle::intersection(std::array<float, 2> point)
    {
        float leftX = mRectangle[0] - (mRectangle[2] / 2.0f);
        float leftY = mRectangle[1] - (mRectangle[3] / 2.0f);

        float rightX = mRectangle[0] + (mRectangle[2] / 2.0f);
        float rightY = mRectangle[1] + (mRectangle[3] / 2.0f);

        return (point[0] >= leftX && point[0] <= rightX &&
                point[1] >= leftY && point[1] <= rightY);
    }

    const std::array<float, 4> Rectangle::getRectangle() const
    {
        return mRectangle;
    }

}}
