#include "IShape.h"

namespace liquid { namespace shape {
#ifndef _CIRCLE_H
#define _CIRCLE_H

/**
 * \class Circle
 *
 * \ingroup Shape
 * \brief Define a circle in 2D space, with (x, y) coordinates and a radius
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 02/05/2017
 *
 */

class Circle : public IShape
{
public:
    /// Circle Constructor
    Circle();

    /// Circle Destructor
    ~Circle();

    /** \brief Defines how the Circle is represented in space
      * \param circle Circle where the Array represents (x, y, radius)
      */
    void setCircle(std::array<float, 3> circle);

    /** \brief Defines how the Circle is represented in space
      * \param x Origin of the Circle on the X-Axis
      * \param y Origin of the Circle on the Y-Axis
      * \param radius Radius of the circle from the origin (x, y)
      */
    void setCircle(float x, float y, float radius);

    /** \brief Override for Circle-Rectangle intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(Rectangle& rectangle) override;

    /** \brief Override for Circle-Circle intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(Circle& circle) override;

    /** \brief Override for Circle-LineSegment intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(LineSegment& line) override;

    /** \brief Override for Circle-Point intersection
      * \param point Array representing a point in 2D-space (x, y)
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(std::array<float, 2> point) override;

    /** \brief Gets the std::array representing the Circle
      * \return mCircle representing the Circle (x, y, radius)
      */
    const std::array<float, 3> getCircle() const;

protected:
    std::array<float, 3> mCircle; ///< Array storing the Circle as (x, y, radius)
};

#endif // _CIRCLE_H
}}
