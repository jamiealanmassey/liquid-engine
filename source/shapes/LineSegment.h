#include "IShape.h"
#include "Vector2.h"

namespace liquid { namespace shape {
#ifndef _LINESEGMENT_H
#define _LINESEGMENT_H

/**
 * \class LineSegment
 *
 * \ingroup Shape
 * \brief Define a finite line in 2D space, with (x1, y1, x2, y2) coordinates in 2D-Space
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 02/05/2017
 *
 */

class LineSegment : public IShape
{
public:
    /** \brief LineSegment Constructor
      * \param segment Segment represented as std::array, where (x1, y1, x2, y2)
      */
    LineSegment(std::array<float, 4> segment);

    /** \brief LineSegment Constructor
      * \param x1 Point1 coordinate on the X-Axis
      * \param y1 Point1 coordinate on the Y-Axis
      * \param x2 Point2 coordinate on the X-Axis
      * \param y2 Point2 coordinate on the Y-Axis
      */
    LineSegment(float x1, float y1, float x2, float y2);

    /// LineSegment Destructor
    ~LineSegment();

    /** \brief Defines the LineSegment in 2D-space
      * \param segment LineSegment where the Array represents (x1, y1, x2, y2)
      */
    virtual void setLine(std::array<float, 4> segment);

    /** \brief Defines the LineSegment in 2D-space
      * \param x1 Point1 coordinate on the X-Axis
      * \param y1 Point1 coordinate on the Y-Axis
      * \param x2 Point2 coordinate on the X-Axis
      * \param y2 Point2 coordinate on the Y-Axis
      */
    virtual void setLine(float x1, float y1, float x2, float y2);

    /** \brief Override for LineSegment-Rectangle intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(Rectangle& rectangle) override;

    /** \brief Override for LineSegment-Circle intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(Circle& circle) override;

    /** \brief Override for LineSegment-LineSegment intersection
      * \param rectangle Shape to test
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(LineSegment& line) override;

    /** \brief Override for LineSegment-Point intersection
      * \param point Array representing a point in 2D-space (x, y)
      * \return True if intersected, otherwise false
      */
    virtual bool intersection(std::array<float, 2> point) override;

    /** \brief Gets the std::array representing the LineSegment
      * \return mLineSegment representing the LineSegment (x1, y1, x2, y2)
      */
    const std::array<float, 4> getLineSegment() const;

    /** \brief Gets the direction of the LineSegment
      * \return Direction of the LineSegment as a Vector2
      */
    const Vector2& getDirection() const;

protected:
    std::array<float, 4> mLineSegment; ///< Array storing the LineSegment as (x1, y1, x2, y2)
    Vector2              mDirection;   ///< Direction Vector2 of the LineSegment
};

#endif // _LINESEGMENT_H
}}
