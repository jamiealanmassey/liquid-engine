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

        return (distanceX <= sizeX && distanceY <= sizeY);
    }

    bool Rectangle::intersection(Circle& circle)
    {
        if (intersection({ circle.getCircle()[0], circle.getCircle()[1] }))
            return true;

        float halfSizeX = mRectangle[2] / 2.0f;
        float halfSizeY = mRectangle[3] / 2.0f;

        LineSegment line0(mRectangle[0] - halfSizeX, mRectangle[1] - halfSizeY, mRectangle[0] + halfSizeX, mRectangle[1] - halfSizeY);
        LineSegment line1(mRectangle[0] + halfSizeX, mRectangle[1] - halfSizeY, mRectangle[0] + halfSizeX, mRectangle[1] + halfSizeY);
        LineSegment line2(mRectangle[0] + halfSizeX, mRectangle[1] + halfSizeY, mRectangle[0] - halfSizeX, mRectangle[1] + halfSizeY);
        LineSegment line3(mRectangle[0] - halfSizeX, mRectangle[1] + halfSizeY, mRectangle[0] - halfSizeX, mRectangle[1] - halfSizeY);

        return (circle.intersection(line0) || circle.intersection(line1) || 
                circle.intersection(line2) || circle.intersection(line3));
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
