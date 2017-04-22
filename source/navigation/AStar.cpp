#include "AStar.h"
#include "../utilities/PriorityQueue.h"

namespace liquid {
namespace navigation {

    AStar::AStar()
    {
        mNavGraphPtr = nullptr;
        mHeuristicFunc = AStar::manhattanHeuristic;
    }

    AStar::AStar(NavGraph* navGraphPtr)
    {
        mNavGraphPtr = navGraphPtr;
        mHeuristicFunc = AStar::manhattanHeuristic;
    }

    AStar::~AStar()
    {
        mNavGraphPtr = nullptr;
    }

    NavPath AStar::search(int32_t sourceNode, int32_t targetNode)
    {
        if (targetNode == INVALID_NAV_NODE || sourceNode == targetNode)
            return NavPath(mNavGraphPtr);

        if (mNavGraphPtr->getNavNode(targetNode).isTraversable() == false)
        {
            NavPath path(mNavGraphPtr);
            path.pushFront(sourceNode);
            return path;
        }

        NavGraph::NavNodeCollection nodes = mNavGraphPtr->getNodesAsReference();
        NavGraph::NavEdgeCollection edges = mNavGraphPtr->getEdgesAsReference();
        NavNode& source = nodes[sourceNode];
        NavNode& target = nodes[targetNode];
        int32_t numNodes = mNavGraphPtr->getNumNavNodes();

        utilities::PriorityQueue<int32_t> openList(numNodes, 
            std::bind(&AStar::compareNodes, this, std::placeholders::_1, std::placeholders::_2));
        
        std::unordered_set<int32_t> closedList(numNodes);
        std::vector<int32_t> cameFrom(numNodes);

        mGCosts.resize(numNodes, 0.0f);
        mFCosts.resize(numNodes, 0.0f);
        cameFrom.resize(numNodes, INVALID_NAV_NODE);
        openList.insert(sourceNode);

        mGCosts[sourceNode] = 0.0;
        mFCosts[sourceNode] = mHeuristicFunc({ source.getPositionX(), source.getPositionY() },
                                             { target.getPositionX(), target.getPositionY() });

        while (openList.isEmpty() == false)
        {
            int32_t closestNode = openList.pop(0);
            closedList.insert(closestNode);

            if (closestNode == targetNode)
                break;

            NavGraph::NavEdgeList::iterator it = edges[closestNode].begin();
            for (; it != edges[closestNode].end(); ++it)
            {
                if (closedList.find((*it).getEdgeTo()) != closedList.end())
                    continue;

                if (nodes[(*it).getEdgeTo()].isTraversable() == false)
                    continue;

                float positionX = nodes[(*it).getEdgeTo()].getPositionX();
                float positionY = nodes[(*it).getEdgeTo()].getPositionY();
                float tarPositionX = nodes[targetNode].getPositionX();
                float tarPositionY = nodes[targetNode].getPositionY();

                std::array<float, 2> position = { positionX, positionY };
                std::array<float, 2> tarPosition = { tarPositionX, tarPositionY };

                float gCost = (float)(mGCosts[closestNode] + (*it).getCost());
                float hCost = (float)(mHeuristicFunc(position, tarPosition));
                bool isOpen = openList.contains((*it).getEdgeTo());

                if (isOpen == false || gCost < mGCosts[(*it).getEdgeTo()])
                {
                    cameFrom[(*it).getEdgeTo()] = closestNode;
                    mGCosts[(*it).getEdgeTo()] = gCost;
                    mFCosts[(*it).getEdgeTo()] = gCost + hCost;

                    if (openList.contains((*it).getEdgeTo()) == false)
                        openList.insert((*it).getEdgeTo());
                    else
                        openList.updatePriority((*it).getEdgeTo());
                }
            }

            NavPath path(mNavGraphPtr);
            if (openList.isEmpty())
                return path;

            int32_t node = targetNode;
            while (node != sourceNode)
            {
                path.pushFront(node);
                node = cameFrom[node];
            }

            path.pushFront(sourceNode);
            return path;
        }
    }

    void AStar::setNavGraphPtr(NavGraph* navGraphPtr)
    {
        mNavGraphPtr = navGraphPtr;
    }

    void AStar::setHeuristicFunc(HeuristicFunc func)
    {
        mHeuristicFunc = func;
    }

    const NavGraph* AStar::getNavGraphPtr() const
    {
        return mNavGraphPtr;
    }

    const std::vector<double>& AStar::getGCosts() const
    {
        return mGCosts;
    }

    const std::vector<double>& AStar::getFCosts() const
    {
        return mFCosts;
    }

    bool AStar::compareNodes(int32_t a, int32_t b)
    {
        return (mFCosts[a] < mFCosts[b]);
    }

    double AStar::manhattanHeuristic(std::array<float, 2> v1, std::array<float, 2> v2)
    {
        double differenceX = std::fabs(v1[0] - v2[0]);
        double differenceY = std::fabs(v1[1] - v2[1]);
        return (differenceX + differenceY);
    }

    double AStar::euclidianHeuristic(std::array<float, 2> v1, std::array<float, 2> v2)
    {
        double differenceX = v1[0] - v2[0];
        double differenceY = v1[1] - v2[1];
        return std::sqrt(std::pow(differenceX, 2) + std::pow(differenceY, 2));
    }

}}
