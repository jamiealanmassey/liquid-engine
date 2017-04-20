#include "NavGraph.h"

namespace liquid {
namespace navigation {

    NavGraph::NavGraph()
    {}

    NavGraph::NavGraph(bool isDirected)
    {}

    NavGraph::~NavGraph()
    {}

    void NavGraph::update()
    {}

    const NavNode& NavGraph::getNavNode(int32_t index) const
    {
        return NavNode(0);
    }

    NavNode& NavGraph::getNavNode(int32_t index)
    {
        return NavNode(0);
    }

    const int32_t NavGraph::getNodeIndex(float x, float y) const
    {
        return INVALID_NAV_NODE;
    }

    const int32_t NavGraph::getNodeIndex(std::array<float, 2> position) const
    {
        return INVALID_NAV_NODE;
    }

    const NavEdge& NavGraph::getNavEdge(int32_t from, int32_t to) const
    {
        return NavEdge();
    }

    NavEdge& NavGraph::getNavEdge(int32_t from, int32_t to)
    {
        return NavEdge();
    }

    int32_t NavGraph::addNavNode(float x, float y, bool traversable)
    {
        return INVALID_NAV_NODE;
    }

    int32_t NavGraph::addNavNode(std::array<float, 2> position, bool traversable)
    {
        return INVALID_NAV_NODE;
    }

    void NavGraph::addNavEdge(int32_t from, int32_t to, double cost)
    {}

    void NavGraph::removeEdge(int32_t from, int32_t to)
    {}

    const bool NavGraph::isNavNodePresent(int32_t index) const
    {
        return true;
    }

    const bool NavGraph::isNavEdgePresent(int32_t from, int32_t to) const
    {
        return true;
    }

    const bool NavGraph::isNavEdgeUnique(int32_t from, int32_t to) const
    {
        return true;
    }

    void NavGraph::setDirected(bool flag)
    {}

    void NavGraph::clear()
    {}
    void NavGraph::removeEdges()
    {}
    void NavGraph::cullInvalidEdges()
    {}

    const int32_t NavGraph::getNumNavEdges() const
    {
        return INVALID_NAV_NODE;
    }

    const int32_t NavGraph::getNumNavNodes() const
    {
        return INVALID_NAV_NODE;
    }

    const int32_t NavGraph::getNumNavNodesActive() const
    {
        return INVALID_NAV_NODE;
    }

    const bool NavGraph::isEmpty() const
    {
        return true;
    }

    const bool NavGraph::isDirected() const
    {
        return true;
    }

}}
