#include "NavNode.h"
#include "NavEdge.h"
#include <list>
#include <vector>

namespace liquid { namespace navigation {
#ifndef _NAVGRAPH_H
#define _NAVGRAPH_H

/**
 * \class NavGraph
 *
 * \ingroup Navigation
 * \brief Stores two collections of nodes and edges in an ordered way for query and use by the NavPath and AStar classes
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 22/04/2017
 *
 */

class NavGraph
{
public:
    /// Defines a simple list of NavEdge objects
    typedef std::list<NavEdge> NavEdgeList;

    /// Defines a collection of NavNode objects
    typedef std::vector<NavNode> NavNodeCollection;

    /// Defines a collection of NavEdgeList's : std::vector(std::list(NavEdge))
    typedef std::vector<NavEdgeList> NavEdgeCollection;

public:
    /// NavGraph Constructor
    NavGraph();

    /** \brief NavGraph Constructor
      * \param isDirection If set to true then when connecting edges they will only be one-way
      */
    NavGraph(bool isDirected);

    /// NavGraph Destructor
    ~NavGraph();

    /// \brief Updates the NavGraph (note: mostly unused)
    virtual void update();

    /** \brief Gets a NavNode object from mNodes
      * \param index Index of the NavNode to get
      * \return Reference to the found NavNode, if none found it will have an index of -1
      */
    const NavNode& getNavNode(int32_t index) const;

    /** \brief Gets a NavNode object from mNodes
      * \param index Index of the NavNode to get
      * \return Reference to the found NavNode, if none found it will have an index of -1
      */
    NavNode& getNavNode(int32_t index);

    /** \brief Gets the NavNode index using the position of the node
      * \param x Position of the node on the X-Axis
      * \param y Position of the node on the Y-Axis
      * \return Index of the found node, -1 if not found
      */
    const int32_t getNodeIndex(float x, float y) const;

    /** \brief Gets the NavNode index using the position of the node
      * \param position Array that represents the position of the NavNode
      * \return Index of the found node, -1 if not found
      */
    const int32_t getNodeIndex(std::array<float, 2> position) const;

    /** \brief Gets the NavEdge that is connected between two NavNode objects
      * \param from Index of the NavNode that the edge comes from
      * \param to Index of the NavNode that the edge goes to
      * \return Reference to the found NavEdge, has an index of -1 otherwise
      */
    const NavEdge& getNavEdge(int32_t from, int32_t to) const;
    
    /** \brief Gets the NavEdge that is connected between two NavNode objects
      * \param from Index of the NavNode that the edge comes from
      * \param to Index of the NavNode that the edge goes to
      * \return Reference to the found NavEdge, has an index of -1 otherwise
      */
    NavEdge& getNavEdge(int32_t from, int32_t to);

    /** \brief Adds a new NavNode object to this NavGraph
      * \param x Position in the world on the X-Axis
      * \param y Position in the world on the Y-Axis
      * \param traversable Denotes if the node can be traversed, default: true
      * \return Generated index of the newly added NavNode
      */
    int32_t addNavNode(float x, float y, bool traversable = true);

    /** \brief Adds a new NavNode object to this NavGraph
      * \param position Array that represents the position of the NavNode
      * \param traversable Denotes if the node can be traversed, default: true
      * \return Generated index of the newly added NavNode
      */
    int32_t addNavNode(std::array<float, 2> position, bool traversable = true);

    /** \brief Adds a new edge between two NavNode objects
      * \param from Index of the NavNode the edge comes from
      * \param to Index of the NavNode the edge goes to
      */
    void addNavEdge(int32_t from, int32_t to, double cost = 1.0f);

    /** \brief Remove an edge between two NavNode objects
      * \param from Index of the NavNode that the edge comes from
      * \param to Index of the NavNode that the edge goes to
      */
    void removeEdge(int32_t from, int32_t to);

    /** \brief Checks to see if the NavNode is present already in this NavGraph
      * \param index Index of the NavNode to check
      * \return True if the node is already in the graph, otherwise false
      */
    const bool isNavNodePresent(int32_t index) const;

    /** \brief Checks to see if the NavEdge is present already in this NavGraph
      * \param from Index of the NavNode that the edge comes from
      * \param to Index of the NavNode that the edge goes to
      * \return True if the edge is already in the graph, otherwise false
      */
    const bool isNavEdgePresent(int32_t from, int32_t to) const;

    /** \brief Checks to see if this NavEdge is unique
      * \param from Index of the NavNode that the edge comes from
      * \param to Index of the NavNode that the edge goes to
      * \return True if it is unique, otherwise false
      */
    const bool isNavEdgeUnique(int32_t from, int32_t to) const;

    /** \brief Sets if the graph is directed or not
      * \param flag Boolean value to assign
      */
    void setDirected(bool flag);

    /// \brief Clears the NavGraph of all NavNode and NavEdge objects
    void clear();

    /// \brief Removes all NavEdge objects
    void removeEdges();

    /// \brief Culls any NavEdge objects that are not required
    void cullInvalidEdges();

    /// \return Gets the number of NavEdge objects stored
    const int32_t getNumNavEdges() const;

    /// \return Gets the number of NavNode objects stored
    const int32_t getNumNavNodes() const;

    /// \return Gets number of NavNode objects that are currently active
    const int32_t getNumNavNodesActive() const;

    /// \return True if the Graph is empty, otherwise false
    const bool isEmpty() const;

    /// \return True if the Graph is directed, otherwise false
    const bool isDirected() const;

    /// \return Gets all the NavNode objects stored
    NavNodeCollection& getNodesAsReference();

    /// \return Gets all the std::list(NavEdge) objects stored
    NavEdgeCollection& getEdgesAsReference();

protected:
    bool              mDirected; ///< Denotes if this NavGraph is directed or not
    NavNodeCollection mNodes;    ///< Stored collection of NavNode objects
    NavEdgeCollection mEdges;    ///< Stored collection of std::list(NavEdge) objects
};

#endif // _NAVGRAPH_H
}}
