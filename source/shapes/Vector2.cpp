#include "Vector2.h"

namespace liquid {
namespace shape {

    Vector2::Vector2()
    {
    }

    Vector2::Vector2(float directionX, float directionY)
    {
        mVectorX = directionX;
        mVectorY = directionY;
    }

    Vector2::~Vector2()
    {
    }

    void Vector2::setVectorX(float vectorX)
    {
        mVectorX = vectorX;
    }

    void Vector2::setVectorY(float vectorY)
    {
        mVectorY = vectorY;
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
        mVectorX *= -1;
    }

    void Vector2::invertY()
    {
        mVectorY *= -1;
    }

    void Vector2::scale(float magnitude)
    {
        mVectorX *= magnitude;
        mVectorY *= magnitude;
    }

    void Vector2::polar(float magnitude, float angle)
    {
        mVectorX = magnitude * std::cos(angle);
        mVectorY = magnitude * std::sin(angle);
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
        float productX = mVectorX * other.getVectorX();
        float productY = mVectorY * other.getVectorY();
        return productX + productY;
    }

    const float Vector2::lineProduct(Vector2& other)
    {
        float productX = mVectorX * other.getVectorY();
        float productY = mVectorY * other.getVectorX();
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

        float rotatedX = mVectorX * cos - mVectorY * sin;
        float rotatedY = mVectorX * sin + mVectorY * cos;

        return Vector2(rotatedX, rotatedY);
    }

    Vector2& Vector2::normalise()
    {
        float magnitude = getMagnitude();
        float normalX = mVectorX / magnitude;
        float normalY = mVectorY / magnitude;

        return Vector2(normalX, normalY);
    }

    Vector2& Vector2::lineNormal()
    {
        return rotate(PI * -0.5f);
    }

    const float Vector2::getVectorX()
    {
        return mVectorX;
    }

    const float Vector2::getVectorY()
    {
        return mVectorY;
    }

    const float Vector2::getMagnitude()
    {
        return std::sqrt(mVectorX * mVectorX + mVectorY * mVectorY);
    }

    const float Vector2::getAngle()
    {
        return std::atan2(mVectorX, mVectorY);
    }

    Vector2& Vector2::operator= (const float scalar)
    {
        mVectorX = scalar;
        mVectorY = scalar;
        return *this;
    }

    Vector2& Vector2::operator- (const float scalar)
    {
        float vectorX = mVectorX - scalar;
        float vectorY = mVectorY - scalar;
        return Vector2(vectorX, vectorY);
    }

    Vector2& Vector2::operator+ (const float scalar)
    {
        float vectorX = mVectorX + scalar;
        float vectorY = mVectorY + scalar;
        return Vector2(vectorX, vectorY);
    }

    Vector2& Vector2::operator* (const float scalar)
    {
        float vectorX = mVectorX * scalar;
        float vectorY = mVectorY * scalar;
        return Vector2(vectorX, vectorY);
    }

    Vector2& Vector2::operator/ (const float scalar)
    {
        float vectorX = mVectorX / scalar;
        float vectorY = mVectorY / scalar;
        return Vector2(vectorX, vectorY);
    }

    Vector2& Vector2::operator+= (const float scalar)
    {
        mVectorX += scalar;
        mVectorY += scalar;
        return *this;
    }

    Vector2& Vector2::operator-= (const float scalar)
    {
        mVectorX -= scalar;
        mVectorY -= scalar;
        return *this;
    }

    Vector2& Vector2::operator*= (const float scalar)
    {
        mVectorX *= scalar;
        mVectorY *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/= (const float scalar)
    {
        mVectorX /= scalar;
        mVectorY /= scalar;
        return *this;
    }

    bool Vector2::operator== (const float scalar)
    {
        return (mVectorX == scalar && mVectorY == scalar);
    }

    Vector2& Vector2::operator= (Vector2& vector)
    {
        mVectorX = vector.getVectorX();
        mVectorY = vector.getVectorY();
        return *this;
    }

    Vector2& Vector2::operator- (Vector2& vector)
    {
        float directionX = mVectorX - vector.getVectorX();
        float directionY = mVectorY - vector.getVectorY();
        return Vector2(directionX, directionY);
    }

    Vector2& Vector2::operator+ (Vector2& vector)
    {
        float directionX = mVectorX + vector.getVectorX();
        float directionY = mVectorY + vector.getVectorY();
        return Vector2(directionX, directionY);
    }

    Vector2& Vector2::operator* (Vector2& vector)
    {
        float directionX = mVectorX * vector.getVectorX();
        float directionY = mVectorY * vector.getVectorY();
        return Vector2(directionX, directionY);
    }

    Vector2& Vector2::operator/ (Vector2& vector)
    {
        float directionX = mVectorX / vector.getVectorX();
        float directionY = mVectorY / vector.getVectorY();
        return Vector2(directionX, directionY);
    }

    Vector2& Vector2::operator+= (Vector2& vector)
    {
        mVectorX += vector.getVectorX();
        mVectorY += vector.getVectorY();
        return *this;
    }

    Vector2& Vector2::operator-= (Vector2& vector)
    {
        mVectorX -= vector.getVectorX();
        mVectorY -= vector.getVectorY();
        return *this;
    }

    Vector2& Vector2::operator*= (Vector2& vector)
    {
        mVectorX *= vector.getVectorX();
        mVectorY *= vector.getVectorY();
        return *this;
    }

    Vector2& Vector2::operator/= (Vector2& vector)
    {
        mVectorX /= vector.getVectorX();
        mVectorY /= vector.getVectorY();
        return *this;
    }

    bool Vector2::operator== (Vector2& vector)
    {
        return (mVectorX == vector.getVectorX() &&
                mVectorY == vector.getVectorY());
    }

}}
