#include "NavGraph.h"
#include <iostream>

namespace liquid {
namespace navigation {

    NavGraph::NavGraph()
    {
        mDirected = false;
    }

    NavGraph::NavGraph(bool isDirected)
    {
        mDirected = isDirected;
    }

    NavGraph::~NavGraph()
    {}

    void NavGraph::update()
    {}

    const NavNode& NavGraph::getNavNode(int32_t index) const
    {
        if (index > mNodes.size() || index < 0)
        {
            std::cout << "<NavGraph::getNavNode> invalid node index" << std::endl;
            return NavNode(INVALID_NAV_NODE);
        }

        return mNodes[index];
    }

    NavNode& NavGraph::getNavNode(int32_t index)
    {
        if (index > mNodes.size() || index < 0)
        {
            std::cout << "<NavGraph::getNavNode> invalid node index" << std::endl;
            return NavNode(INVALID_NAV_NODE);
        }

        return mNodes[index];
    }

    const int32_t NavGraph::getNodeIndex(float x, float y) const
    {
        for (uint32_t i = 0; i < mNodes.size(); i++)
        {
            if (mNodes[i].getPositionX() == x && mNodes[i].getPositionY() == y)
                return mNodes[i].getNodeIndex();
        }

        return INVALID_NAV_NODE;
    }

    const int32_t NavGraph::getNodeIndex(std::array<float, 2> position) const
    {
        return getNodeIndex(position[0], position[1]);
    }

    const NavEdge& NavGraph::getNavEdge(int32_t from, int32_t to) const
    {
        if (from > mNodes.size() || from < 0 || mNodes[from].getNodeIndex() == INVALID_NAV_NODE)
        {
            std::cout << "<NavGraph::getNavEdge> invalid 'from' index" << std::endl;
            return NavEdge(INVALID_NAV_NODE, INVALID_NAV_NODE);
        }

        if (to > mNodes.size() || to < 0 || mNodes[to].getNodeIndex() == INVALID_NAV_NODE)
        {
            std::cout << "<NavGraph::getNavEdge> invalid 'to' index" << std::endl;
            return NavEdge(INVALID_NAV_NODE, INVALID_NAV_NODE);
        }

        NavEdgeList::const_iterator curEdge = mEdges[from].begin();
        for (; curEdge != mEdges[from].end(); ++curEdge)
        {
            if (curEdge->getEdgeTo() == to)
                return (*curEdge);
        }

        std::cout << "<NavGraph::getNavEdge> could not find an edge" << std::endl;
        return NavEdge();
    }

    NavEdge& NavGraph::getNavEdge(int32_t from, int32_t to)
    {
        if (from > mNodes.size() || from < 0 || mNodes[from].getNodeIndex() == INVALID_NAV_NODE)
        {
            std::cout << "<NavGraph::getNavEdge> invalid 'from' index" << std::endl;
            return NavEdge(INVALID_NAV_NODE, INVALID_NAV_NODE);
        }

        if (to > mNodes.size() || to < 0 || mNodes[to].getNodeIndex() == INVALID_NAV_NODE)
        {
            std::cout << "<NavGraph::getNavEdge> invalid 'to' index" << std::endl;
            return NavEdge(INVALID_NAV_NODE, INVALID_NAV_NODE);
        }

        NavEdgeList::iterator curEdge = mEdges[from].begin();
        for (; curEdge != mEdges[from].end(); ++curEdge)
        {
            if (curEdge->getEdgeTo() == to)
                return (*curEdge);
        }

        std::cout << "<NavGraph::getNavEdge> could not find an edge" << std::endl;
        return NavEdge();
    }

    int32_t NavGraph::addNavNode(float x, float y, bool traversable)
    {
        int32_t index = mNodes.size();
        NavNode node(index);
        node.setPosition(x, y);
        node.setTraversable(traversable);

        mNodes.push_back(node);
        mEdges.push_back(NavEdgeList());
        return index;
    }

    int32_t NavGraph::addNavNode(std::array<float, 2> position, bool traversable)
    {
        return addNavNode(position[0], position[1], traversable);
    }

    void NavGraph::addNavEdge(int32_t from, int32_t to, double cost)
    {
        if (mNodes[to].getNodeIndex() != INVALID_NAV_NODE &&
            mNodes[from].getNodeIndex() != INVALID_NAV_NODE)
        {
            if (isNavEdgeUnique(from, to))
                mEdges[from].push_back(NavEdge(from, to, cost));

            if (mDirected == false && isNavEdgeUnique(to, from))
                mEdges[to].push_back(NavEdge(to, from, cost));
        }
    }

    void NavGraph::removeEdge(int32_t from, int32_t to)
    {
        if ((from > mNodes.size() || from < 0) || (to > mNodes.size() || to < 0))
        {
            std::cout << "<NavGraph::removeEdge> given nodes don't exist" << std::endl;
            return;
        }

        NavEdgeList::iterator curEdge;
        if (mDirected == false)
        {
            for (curEdge = mEdges[to].begin(); curEdge != mEdges[to].end(); ++curEdge)
            {
                if (curEdge->getEdgeTo() == from)
                {
                    curEdge = mEdges[to].erase(curEdge);
                    break;
                }
            }
        }

        for (curEdge = mEdges[from].begin(); curEdge != mEdges[from].end(); ++curEdge)
        {
            if (curEdge->getEdgeTo() == to)
            {
                curEdge = mEdges[from].erase(curEdge);
                break;
            }
        }
    }

    const bool NavGraph::isNavNodePresent(int32_t index) const
    {
        return (index >= 0 && index < mNodes.size() && 
                mNodes[index].getNodeIndex() != INVALID_NAV_NODE);
    }

    const bool NavGraph::isNavEdgePresent(int32_t from, int32_t to) const
    {
        if (isNavNodePresent(from) && isNavNodePresent(to))
        {
            NavEdgeList::const_iterator curEdge = mEdges[from].begin();
            for (; curEdge != mEdges[from].end(); ++curEdge)
            {
                if (curEdge->getEdgeTo() == to)
                    return true;
            }
        }

        return false;
    }

    const bool NavGraph::isNavEdgeUnique(int32_t from, int32_t to) const
    {
        NavEdgeList::const_iterator curEdge = mEdges[from].begin();
        for (; curEdge != mEdges[from].end(); ++curEdge)
        {
            if (curEdge->getEdgeTo() == to)
                return false;
        }

        return true;
    }

    void NavGraph::setDirected(bool flag)
    {
        mDirected = flag;
    }

    void NavGraph::clear()
    {
        mNodes.clear();
        mEdges.clear();
    }

    void NavGraph::removeEdges()
    {
        for (NavEdgeCollection::iterator it = mEdges.begin(); it != mEdges.end(); ++it)
            it->clear();
    }

    void NavGraph::cullInvalidEdges()
    {
        for (NavEdgeCollection::iterator curEdges = mEdges.begin(); curEdges != mEdges.end(); ++curEdges)
        {
            for (NavEdgeList::iterator curEdge = (*curEdges).begin(); curEdge != (*curEdges).end(); ++curEdge)
            {
                if (mNodes[curEdge->getEdgeTo()].getNodeIndex() == INVALID_NAV_NODE ||
                    mNodes[curEdge->getEdgeFrom()].getNodeIndex() == INVALID_NAV_NODE)
                {
                    curEdge = (*curEdges).erase(curEdge);
                }
            }
        }
    }

    const int32_t NavGraph::getNumNavEdges() const
    {
        int32_t count = 0;
        NavEdgeCollection::const_iterator curEdge = mEdges.begin();

        for (; curEdge != mEdges.end(); ++curEdge)
            count += curEdge->size();

        return count;
    }

    const int32_t NavGraph::getNumNavNodes() const
    {
        return mNodes.size();
    }

    const int32_t NavGraph::getNumNavNodesActive() const
    {
        int32_t count = 0;

        for (uint32_t i = 0; i < mNodes.size(); i++)
        {
            if (mNodes[i].getNodeIndex() != INVALID_NAV_NODE)
                count++;
        }

        return count;
    }

    const bool NavGraph::isEmpty() const
    {
        return mNodes.empty();
    }

    const bool NavGraph::isDirected() const
    {
        return mDirected;
    }

}}
