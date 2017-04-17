#include <array>

namespace liquid { namespace utilities {
#ifndef _VERTEX2_H
#define _VERTEX2_H

/** 
 * \class Vertex2
 *
 * \ingroup Utilities
 * \brief Defines a Vertex2 point in 2D-space
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 17/04/2017
 *
 */

class Vertex2
{
public:
    /// Vertex2 Constructor
    Vertex2();

    /** \brief Vertex2 Constructor
      * \param position Position of the Vertex2 (x,y)
      * \param colour Colour of the Vertex2 (r,g,b,a)
      * \param texCoord Texture coordinate of this Vertex2 (x, y)
      */
    Vertex2(std::array<float, 2> position, std::array<float, 4> colour, std::array<float, 2> texCoord);

    /// Vertex2 Destructor
    ~Vertex2();

    /** \brief Set the position of this Vertex2
      * \param position Array of position in 2D-space (x,y)
      */
    void setPosition(std::array<float, 2> position);

    /** \brief Set the position of this Vertex2
      * \param x X-Coordinate of the Vertex2 in 2D space
      * \param y Y-Coordinate of the Vertex2 in 2D space
      */
    void setPosition(float x, float y);

    /** \brief Set the colour of this Vertex2
      * \param colour Array of colour of this Vertex2 (r,g,b,a)
      */
    void setColour(std::array<float, 4> colour);

    /** \brief Set the colour of this Vertex2
      * \param r Red colour of this Vertex2
      * \param g Green colour of this Vertex2
      * \param b Blue colour of this Vertex2
      * \param a Alpha channel of this Vertex2
      */
    void setColour(float r, float g, float b, float a);

    /** \brief Set the texture coordinate of this Vertex2
      * \param texCoord Array of tex coordinate of this Vertex2 (x,y)
      */
    void setTexCoord(std::array<float, 2> texCoord);

    /** \brief Set the position of the texture coordinate for this Vertex2
      * \param x X-Coordinate of the Vertex2 tex coord in 2D space
      * \param y Y-Coordinate of the Vertex2 tex coord in 2D space
      */
    void setTexCoord(float x, float y);

    /// \return Position of this Vertex2
    const std::array<float, 2> getPosition() const;

    /// \return Colour of this Vertex2
    const std::array<float, 4> getColour() const;

    /// \return Texture Coordinate of this Vertex2
    const std::array<float, 2> getTexCoord() const;

protected:
    std::array<float, 2> mPosition; ///< The Position of this Vertex2 in 2D-space
    std::array<float, 4> mColour;   ///< The colour of this Vertex2
    std::array<float, 2> mTexCoord; ///< The position of the Texture Coordinate to use
};

#endif // _VERTEX2_H
}}
