#include "IShape.h"
#include <array>

namespace liquid { namespace shape {
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

/**
 * \class Rectangle
 *
 * \ingroup Shape
 * \brief Define a rectangle in 2D space, with (x, y, w, h) coordinates where x,y is the origin
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 02/05/2017
 *
 */

class Rectangle : public IShape
{
public:
    /// Rectangle Constructor
    Rectangle();

    /// Rectangle Destructor
    ~Rectangle();

    /** \brief Defines how the Rectangle is represented in space
      * \param rectangle Rectangle where the array represents (x, y, w, h)
      */
    void setRectangle(std::array<float, 4> rectangle);

    /** \brief Defines how the Rectangle is represented in space
      * \param x Origin of the Rectangle on the X-Axis
      * \param y Origin of the Rectangle on the Y-Axis
      * \param w Total width of the Rectangle
      * \param h Total height of the Rectangle
      */
    void setRectangle(float x, float y, float w, float h);

    /** \brief Override for Rectangle-Rectangle intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(Rectangle& rectangle) override;

    /** \brief Override for Rectangle-Circle intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(Circle& circle) override;

    /** \brief Override for Rectangle-LineSegment intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(LineSegment& line) override;

    /** \brief Override for Rectangle-Point intersection
      * \param point Array representing a point in 2D-space (x, y)
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(std::array<float, 2> point) override;

    /** \brief Gets the std::array representing the Rectangle
      * \return mRectangle representing the Rectangle (x, y, w, h)
      */
    const std::array<float, 4> getRectangle() const;

protected:
    std::array<float, 4> mRectangle; ///< Array storing the Rectangle as (x, y, w, h)
};

#endif // _RECTANGLE_H
}}
