#include "NavGraph.h"
#include "NavNode.h"
#include "NavEdge.h"
#include "NavPath.h"
#include <functional>
#include <array>
#include <unordered_set>

namespace liquid { namespace navigation {
#ifndef _ASTAR_H
#define _ASTAR_H

/**
 * \class AStar
 *
 * \ingroup Navigation
 * \brief Implements the A* pathfinding algorithm using a given NavGraph and produces a NavPath
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 22/04/2017
 *
 */

class AStar
{
public:
    /// Defines a Heuristic Function to calculate cost values
    typedef std::function<double(std::array<float, 2>, std::array<float, 2>)> HeuristicFunc;

public:
    /// AStar Constructor
    AStar();

    /** \brief AStar Constructor
      * \param navGraphPtr Pointer to NavGraph that stores NavNode and NavEdge objects
      */
    AStar(NavGraph* navGraphPtr);

    /// AStar Destructor
    ~AStar();

    /** \brief Executes the search algorithm on the given NavGraph using given parameters
      * \param sourceNode Index of node from where to start the search
      * \param targetNode Index of node we are looking for
      * \return Calculated NavPath from source to target NavNode
      */
    NavPath search(int32_t sourceNode, int32_t targetNode);

    /** \brief Set the NavGraph pointer
      * \param navGraphPtr Pointer to desired NavGraph
      */
    void setNavGraphPtr(NavGraph* navGraphPtr);

    /** \brief Assigns the Heuristic Function for costs
      * \param func Desired function
      */
    void setHeuristicFunc(HeuristicFunc func);

    /// \return Gets the pointer to the used NavGraph
    const NavGraph* getNavGraphPtr() const;

    /// \return Collection of the GCosts of AStar::search
    const std::vector<double>& getGCosts() const;

    /// \return Collection of the FCosts of AStar::search
    const std::vector<double>& getFCosts() const;

protected:
    /// \brief Comparison function for costs
    bool compareNodes(int32_t a, int32_t b);
    
    /** \brief Manhattan method for costs heuristic
      * \param v1 First vector position to calculate
      * \param v2 Second target vector position to calculate
      * \return Calculated cost by the heuristic
      *
      * where f(v1, v2) = abs(v1.x - v2.x) + abs(v1.y - v2.y)
      */
    static double manhattanHeuristic(std::array<float, 2> v1, std::array<float, 2> v2);

    /** \brief Euclidean method for costs heuristic
      * \param v1 First vector position to calculate
      * \param v2 Second target vector position to calculate
      * \return Calculated cost by the heuristic
      *
      * where f(v1, v2) = (v1.x - v2.x)^2 + (v1.y - v2.y)^2
      */
    static double euclidianHeuristic(std::array<float, 2> v1, std::array<float, 2> v2);

protected:
    NavGraph*           mNavGraphPtr;   ///< Pointer to the NavGraph used for pathfinding
    HeuristicFunc       mHeuristicFunc; ///< Heurstic function to calculate costs
    std::vector<double> mGCosts;        ///< Stored total GCosts
    std::vector<double> mFCosts;        ///< Stored total FCosts
};

#endif //_ASTAR_H
}}
