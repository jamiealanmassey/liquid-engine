#include <stdint.h>

namespace liquid { namespace navigation {
#ifndef _NAVEDGE_H
#define _NAVEDGE_H

#define INVALID_NAV_NODE -1

/**
 * \class NavEdge
 *
 * \ingroup Navigation
 * \brief Defines an edge between two NavNode objects, denoted by their index in the NavGraph
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 22/04/2017
 *
 */

class NavEdge
{
public:
    /// NavEdge Constructor
    NavEdge();

    /** \brief NavEdge Constructor
      * \param from Node index that the edge comes from
      * \param to Node index that the edge goes to
      * \param cost Cost to traverse between the two
      */
    NavEdge(int32_t from, int32_t to, double cost = 1.0f);

    /// NavEdge Destructor
    ~NavEdge();

    /** \brief Sets the node index that the edge comes from
      * \param from Node index edge comes from
      */
    void setEdgeFrom(int32_t from);

    /** \brief Sets the node index that the edge goes to
      * \param from Node index edge goes to
      */
    void setEdgeTo(int32_t to);

    /** \brief Sets the cost to traverse the nodes
      * \param cost Cost of traversing between the NavNode objects
      */
    void setCost(double cost);

    /// \return Get the index of the NavNode the edge comes from
    const int32_t getEdgeFrom() const;

    /// \return Get the index of the NavNode the edge goes to
    const int32_t getEdgeTo() const;

    /// \return Gets the cost to traverse the NavNode objects
    const double getCost() const;

protected:
    int32_t mEdgeFrom; ///< Index of the NavNode the edge comes from
    int32_t mEdgeTo;   ///< Index of the NavNode the edge goes to
    double  mCost;     ///< Cost to traverse between the two NavNode objects
};

#endif // _NAVEDGE_H
}}
