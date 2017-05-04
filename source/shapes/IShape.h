#include <cstdint>
#include <array>

namespace liquid { namespace shape {
#ifndef _ISHAPE_H
#define _ISHAPE_H

/**
 * \class IShape
 *
 * \ingroup Shape
 * \brief Interface class that defines the point count and intersection tests for each shape
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 02/05/2017
 *
 */

class Rectangle;
class Circle;
class LineSegment;
class IShape
{
public:
    /** \brief IShape Constructor
      * \param pointCount Number of points in the shape
      */
    IShape(uint32_t pointCount)
    {
        mPointCount = pointCount;
    }
    
    /// IShape Destructor
    ~IShape()
    {
    }

    /** \brief Gets the number of points in the shape
      * \return Number of points as a uint32_t
      */
    const uint32_t getPointCount() const
    {
        return mPointCount;
    }

    /** \brief Pure virtual intersection test for a Rectangle
      * \param rectangle Shape to test against
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(Rectangle& rectangle) = 0;

    /** \brief Pure virtual intersection test for a Circle
      * \param circle Shape to test against
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(Circle& circle) = 0;

    /** \brief Pure virtual intersection test for a LineSegment
      * \param line Shape to test against
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(LineSegment& line) = 0;

    /** \brief Pure virtual intersection test for a Point (x, y)
      * \param point Array representing a point in 2D-space (x, y)
      * \return True if inside, otherwise false
      */
    virtual bool intersection(std::array<float, 2> point) = 0;

protected:
    uint32_t mPointCount; ///< Number of points in the shape
};

#endif // _ISHAPE_H
}}
