#include <cmath>
#include <algorithm>

namespace liquid { namespace shape {
#ifndef _VECTOR2_H
#define _VECTOR2_H

#define PI 3.14159265359

/**
 * \class Vector2
 *
 * \ingroup Shape
 * \brief Defines a direction in 2D-Space using (x, y)
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class Vector2
{
public:
    /// Vector2 Constructor
    Vector2();

    /** \brief Vector2 Constructor
      * \param directionX Direction of the Vector on the X-Axis
      * \param directionY Direction of the Vector on the Y-Axis
      */
    Vector2(float directionX, float directionY);

    /// Vector2 Destructor
    ~Vector2();

    /** \brief Set the Vector2 X-Axis component
      * \param vectorX X-Axis component
      */
    void setVectorX(float vectorX);

    /** \brief Set the Vector2 Y-Axis component
      * \param vectorY Y-Axis component
      */
    void setVectorY(float vectorY);

    /** \brief Set the angle of the Vector2
      * \param angle Angle to be assigned to the Vector2
      */
    void setAngle(float angle);

    /** \brief Sets the length/magnitude of the Vector2
      * \param magnitude Magnitude to be assigned
      */
    void setMagnitude(float magnitude);

    /// \brief Invert the X-Axis value of the Vector2 direction
    void invertX();

    /// \brief Invert the Y-Axis value of the Vector2 direction
    void invertY();

    /** \brief Scale the Vector2 by a magnitude as a scalar value
      * \param magnitude Value to scale the Vector2 by
      */
    void scale(float magnitude);

    /** \brief Calculates the polar vector and assigns it to this Vector2
      * \param magnitude Magnitude of the polar
      * \param angle Angle of the polar
      */
    void polar(float magnitude, float angle);

    /** \brief Calculate the angle against another Vector2 
      * \param other The other Vector2 to calculate against
      */
    const float angle(Vector2& other);

    /** \brief Calculate the dot product of this and another Vector2
      * \param other The other Vector2 to calculate against
      */
    const float dotProduct(Vector2& other);

    /** \brief Calculate the line product of this and another Vector2
      * \param other The other Vector2 to calculate against
      */
    const float lineProduct(Vector2& other);

    /** \brief Calculate the projection against another Vector2
      * \param other The other Vector2 to calculate against
      */
    const float projection(Vector2& other);

    /** \brief Calculate the rotation of this Vector2 given an angle
      * \param angle Angle to rotate
      */
    Vector2 rotate(float angle);

    /// \brief Normalise the Vector2 and get its resulting Vector2
    Vector2 normalise();

    /// \brief Get the normals of both Vector2 components (x, y)
    Vector2 lineNormal();

    /// \return Gets the X-Axis component of the Vector2
    float getVectorX() const;

    /// \return Gets the Y-Axis component of the Vector2
    float getVectorY() const;

    /// \return Gets the magnitude component of the Vector2
    const float getMagnitude();

    /// \return Gets the angle of the Vector2
    const float getAngle();

    /// \brief Takes a scalar and assigns the value to both (x, y)
    Vector2 operator= (const float scalar);

    /// \brief Takes a scalar and take it away from both components (x, y)
    Vector2 operator- (const float scalar);

    /// \brief Takes a scalar and adds it to both components (x, y)
    Vector2 operator+ (const float scalar);

    /// \brief Takes a scalar and multiplies it with both components (x, y)
    Vector2 operator* (const float scalar);

    /// \brief Takes a scalar and divides it against both components (x, y)
    Vector2 operator/ (const float scalar);

    /// \brief Takes a scalar and adds it to both components (x, y) and assigns
    Vector2 operator+= (const float scalar);

    /// \brief Takes a scalar and take it away from both components (x, y) and assigns
    Vector2 operator-= (const float scalar);

    /// \brief Takes a scalar and multiplies it with both components (x, y) and assigns
    Vector2 operator*= (const float scalar);

    /// \brief Takes a scalar and divides it against both components (x, y) and assigns
    Vector2 operator/= (const float scalar);

    /// \brief Takes a scalar and compares it against both components(x, y) returning true if they are the same
    bool operator== (const float scalar);

    /// \brief Assigns the vector to this vector
    Vector2 operator= (Vector2& vector);

    /// \brief Takes the vector away from this Vector2
    Vector2 operator- (Vector2& vector);

    /// \brief Adds the vector to this Vector2
    Vector2 operator+ (Vector2& vector);

    /// \brief Multiplies the vector with this Vector2
    Vector2 operator* (Vector2& vector);

    /// \brief Divides the vector against this Vector2
    Vector2 operator/ (Vector2& vector);

    /// \brief Adds the vector to this Vector2 and assigns
    Vector2 operator+= (Vector2& vector);

    /// \brief Takes the vector away from this Vector2 and assigns
    Vector2 operator-= (Vector2& vector);

    /// \brief Multiplies the vector with this Vector2 and assigns
    Vector2 operator*= (Vector2& vector);

    /// \brief Divides the vector against this Vector2 and assigns
    Vector2 operator/= (Vector2& vector);

    /// \brief Compares the two Vector2 objects, if components (x,y) are equal, return true
    bool operator== (Vector2& vector);

protected:
    float mVectorX; ///< X-Axis component of the direction Vector2
    float mVectorY; ///< Y-Axis component of the direction Vector2
};

#define VECTOR2X Vector2(1.0f, 0.0f)
#define VECTOR2Y Vector2(0.0f, 1.0f)
#define VECTOR20 Vector2(0.0f, 0.0f)

#endif // _VECTOR2_H
}}
