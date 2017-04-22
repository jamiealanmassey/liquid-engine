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

class AStar
{
public:
    typedef std::function<double(std::array<float, 2>, std::array<float, 2>)> HeuristicFunc;

public:
    AStar();
    AStar(NavGraph* navGraphPtr);
    ~AStar();

    NavPath search(int32_t sourceNode, int32_t targetNode);

    void setNavGraphPtr(NavGraph* navGraphPtr);
    void setHeuristicFunc(HeuristicFunc func);

    const NavGraph* getNavGraphPtr() const;
    const std::vector<double>& getGCosts() const;
    const std::vector<double>& getFCosts() const;

protected:
    bool compareNodes(int32_t a, int32_t b);
    
    static double manhattanHeuristic(std::array<float, 2> v1, std::array<float, 2> v2);
    static double euclidianHeuristic(std::array<float, 2> v1, std::array<float, 2> v2);

protected:
    NavGraph*           mNavGraphPtr; ///< 
    HeuristicFunc       mHeuristicFunc; ///< 
    std::vector<double> mGCosts; ///< 
    std::vector<double> mFCosts; ///<
};

#endif //_ASTAR_H
}}
