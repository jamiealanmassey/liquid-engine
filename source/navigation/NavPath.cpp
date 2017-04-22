#include "NavPath.h"

namespace liquid {
namespace navigation {

    NavPath::NavPath(NavGraph* navGraphPtr)
    {
        mNavGraphPtr = navGraphPtr;
    }

    NavPath::~NavPath()
    {}

    void NavPath::pushFront(int32_t index)
    {
        mNodes.push_front(index);
    }

    void NavPath::pushBack(int32_t index)
    {
        mNodes.push_back(index);
    }

    const NavNode& NavPath::popFront()
    {
        const NavNode& node = peekFront();
        mNodes.pop_front();
        return node;
    }

    const NavNode& NavPath::popBack()
    {
        const NavNode& node = peekBack();
        mNodes.pop_back();
        return node;
    }

    const NavNode& NavPath::loopFront()
    {
        pushBack(mNodes.front());
        return popFront();
    }

    const NavNode& NavPath::loopBack()
    {
        pushFront(mNodes.back());
        return popBack();
    }

    std::vector<NavNode> NavPath::getNavPath()
    {
        std::vector<NavNode> nodes(mNodes.size());
        std::copy(mNodes.begin(), mNodes.end(), nodes);
        return nodes;
    }

    std::vector<NavNode> NavPath::getNavPathReversed()
    {
        std::vector<NavNode> nodes(mNodes.size());
        std::copy_backward(mNodes.begin(), mNodes.end(), nodes);
        return nodes;
    }

    const bool NavPath::isEmpty() const
    {
        return mNodes.empty();
    }

    const NavNode& NavPath::peekFront() const
    {
        return mNavGraphPtr->getNavNode(mNodes.front());
    }

    const NavNode& NavPath::peekBack() const
    {
        return mNavGraphPtr->getNavNode(mNodes.back());
    }

}}
