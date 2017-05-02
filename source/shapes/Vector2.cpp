#include "Vector2.h"

namespace liquid {
namespace shape {

    Vector2::Vector2()
    {
    }

    Vector2::Vector2(float directionX, float directionY)
    {
        mDirectionX = directionX;
        mDirectionY = directionY;
    }

    Vector2::~Vector2()
    {
    }

    void Vector2::setDirectionX(float directionX)
    {
        mDirectionX = directionX;
    }

    void Vector2::setDirectionY(float directionY)
    {
        mDirectionY = directionY;
    }
    
    void Vector2::setAngle(float angle)
    {
        polar(getMagnitude(), angle);
    }

    void Vector2::setMagnitude(float magnitude)
    {
        polar(magnitude, getAngle());
    }

    void Vector2::invertX()
    {
        mDirectionX *= -1;
    }

    void Vector2::invertY()
    {
        mDirectionY *= -1;
    }

    void Vector2::scale(float magnitude)
    {
        mDirectionX *= magnitude;
        mDirectionY *= magnitude;
    }

    void Vector2::polar(float magnitude, float angle)
    {
        mDirectionX = magnitude * std::cos(angle);
        mDirectionY = magnitude * std::sin(angle);
    }

    const float Vector2::angle(Vector2& other)
    {
        Vector2& normal0 = normalise();
        Vector2& normal1 = other.normalise();

        float product = std::min(normal0.dotProduct(normal1), 1.0f);
        float angle = std::acos(product);

        if (lineProduct(other) < 0.f)
            angle *= -1;

        return angle;
    }

    const float Vector2::dotProduct(Vector2& other)
    {
        float productX = mDirectionX * other.getDirectionX();
        float productY = mDirectionY * other.getDirectionY();
        return productX + productY;
    }

    const float Vector2::lineProduct(Vector2& other)
    {
        float productX = mDirectionX * other.getDirectionY();
        float productY = mDirectionY * other.getDirectionX();
        return productX - productY;
    }

    const float Vector2::projection(Vector2& other)
    {
        return dotProduct(other.normalise());
    }

    Vector2& Vector2::rotate(float angle)
    {
        float cos = std::cos(angle);
        float sin = std::sin(angle);

        float rotatedX = mDirectionX * cos - mDirectionY * sin;
        float rotatedY = mDirectionX * sin + mDirectionY * cos;

        return Vector2(rotatedX, rotatedY);
    }

    Vector2& Vector2::normalise()
    {
        float magnitude = getMagnitude();
        float normalX = mDirectionX / magnitude;
        float normalY = mDirectionY / magnitude;

        return Vector2(normalX, normalY);
    }

    Vector2& Vector2::lineNormal()
    {
        return rotate(PI * -0.5f);
    }

    const float Vector2::getDirectionX()
    {
        return mDirectionX;
    }

    const float Vector2::getDirectionY()
    {
        return mDirectionY;
    }

    const float Vector2::getMagnitude()
    {
        return std::sqrt(mDirectionX * mDirectionX + mDirectionY * mDirectionY);
    }

    const float Vector2::getAngle()
    {
        return std::atan2(mDirectionX, mDirectionY);
    }

    Vector2& Vector2::operator= (Vector2& vector)
    {
        mDirectionX = vector.getDirectionX();
        mDirectionY = vector.getDirectionY();
        return *this;
    }

    Vector2& Vector2::operator- (Vector2& vector)
    {
        float directionX = mDirectionX - vector.getDirectionX();
        float directionY = mDirectionY - vector.getDirectionY();
        return Vector2(directionX, directionY);
    }

    Vector2& Vector2::operator+ (Vector2& vector)
    {
        float directionX = mDirectionX + vector.getDirectionX();
        float directionY = mDirectionY + vector.getDirectionY();
        return Vector2(directionX, directionY);
    }

    Vector2& Vector2::operator* (Vector2& vector)
    {
        float directionX = mDirectionX * vector.getDirectionX();
        float directionY = mDirectionY * vector.getDirectionY();
        return Vector2(directionX, directionY);
    }

    Vector2& Vector2::operator/ (Vector2& vector)
    {
        float directionX = mDirectionX / vector.getDirectionX();
        float directionY = mDirectionY / vector.getDirectionY();
        return Vector2(directionX, directionY);
    }

    Vector2& Vector2::operator+= (Vector2& vector)
    {
        mDirectionX += vector.getDirectionX();
        mDirectionY += vector.getDirectionY();
        return *this;
    }

    Vector2& Vector2::operator-= (Vector2& vector)
    {
        mDirectionX -= vector.getDirectionX();
        mDirectionY -= vector.getDirectionY();
        return *this;
    }

    Vector2& Vector2::operator*= (Vector2& vector)
    {
        mDirectionX *= vector.getDirectionX();
        mDirectionY *= vector.getDirectionY();
        return *this;
    }

    Vector2& Vector2::operator/= (Vector2& vector)
    {
        mDirectionX /= vector.getDirectionX();
        mDirectionY /= vector.getDirectionY();
        return *this;
    }

    bool Vector2::operator== (Vector2& vector)
    {
        return (mDirectionX == vector.getDirectionX() &&
                mDirectionY == vector.getDirectionY());
    }

}}
