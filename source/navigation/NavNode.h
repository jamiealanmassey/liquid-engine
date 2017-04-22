#include <array>

namespace liquid { namespace navigation {
#ifndef _NAVNODE_H
#define _NAVNODE_H

#define INVALID_NAV_NODE -1

/**
 * \class NavNode
 *
 * \ingroup Navigation
 * \brief Defines a node for the Navigation between nodes
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 22/04/2017
 *
 */

class NavNode
{
public:
    /** \brief NavNode Constructor
      * \param index Index of the node to create
      */
    NavNode(int32_t index);

    /// NavNode Destructor
    ~NavNode();

    /** \brief Set the position of this node in relation to the world
      * \param x X-Axis position
      * \param y Y-Axis position
      */
    void setPosition(float x, float y);

    /** \brief Set the position of this node in relation to the world
      * \param position Array of floats representing the position
      */
    void setPosition(std::array<float, 2> position);
    
    /** \brief Denotes if this node can be traversed over
      * \param flag Boolean value to assign traversable to
      */
    void setTraversable(bool flag);

    /** \brief Set the index of this node
      * \param index Value to assign this node to
      */
    void setNodeIndex(int32_t index);

    /// \return Position on the X-Axis
    const float getPositionX() const;

    /// \return Position on the Y-Axis
    const float getPositionY() const;

    /// \return True if can traverse, otherwise false
    const bool isTraversable() const;

    /// \return Gets the index of this node
    const int32_t getNodeIndex() const;

protected:
    float   mPositionX;   ///< Stores the position on the X-Axis
    float   mPositionY;   ///< Stores the position on the Y-Axis
    bool    mTraversable; ///< Denotes if you can traverse this node
    int32_t mNodeIndex;   ///< Current index of this node
};

#endif // _NAVNODE_H
}}
