#include "NavNode.h"
#include "NavEdge.h"
#include <list>
#include <vector>

namespace liquid { namespace navigation {
#ifndef _NAVGRAPH_H
#define _NAVGRAPH_H

class NavGraph
{
public:
    typedef std::list<NavEdge>       NavEdgeList;
    typedef std::vector<NavNode>     NavNodeCollection;
    typedef std::vector<NavEdgeList> NavEdgeCollection;

public:
    NavGraph();
    NavGraph(bool isDirected);
    ~NavGraph();

    virtual void update();

    const NavNode& getNavNode(int32_t index) const;
    NavNode& getNavNode(int32_t index);

    const int32_t getNodeIndex(float x, float y) const;
    const int32_t getNodeIndex(std::array<float, 2> position) const;

    const NavEdge& getNavEdge(int32_t from, int32_t to) const;
    NavEdge& getNavEdge(int32_t from, int32_t to);

    int32_t addNavNode(float x, float y, bool traversable = true);
    int32_t addNavNode(std::array<float, 2> position, bool traversable = true);

    void addNavEdge(int32_t from, int32_t to, double cost = 1.0f);
    void removeEdge(int32_t from, int32_t to);

    const bool isNavNodePresent(int32_t index) const;
    const bool isNavEdgePresent(int32_t from, int32_t to) const;
    const bool isNavEdgeUnique(int32_t from, int32_t to) const;

    void setDirected(bool flag);

    void clear();
    void removeEdges();
    void cullInvalidEdges();

    const int32_t getNumNavEdges() const;
    const int32_t getNumNavNodes() const;
    const int32_t getNumNavNodesActive() const;

    const bool isEmpty() const;
    const bool isDirected() const;

protected:
    bool              mDirected; ///< 
    NavNodeCollection mNodes;    ///< 
    NavEdgeCollection mEdges;    ///< 
};

#endif // _NAVGRAPH_H
}}
