#include "NavGraph.h"
#include "NavNode.h"
#include "NavEdge.h"

namespace liquid { namespace navigation {
#ifndef _NAVPATH_H
#define _NAVPATH_H

class NavPath
{
public:
    NavPath(NavGraph* navGraphPtr);
    ~NavPath();

    void pushFront(int32_t index);
    void pushBack(int32_t index);

    const NavNode& popFront();
    const NavNode& popBack();
    const NavNode& loopFront();
    const NavNode& loopBack();

    std::vector<NavNode> getNavPath();
    std::vector<NavNode> getNavPathReversed();

    const bool isEmpty() const;
    const NavNode& peekFront() const;
    const NavNode& peekBack() const;

protected:
    NavGraph*          mNavGraphPtr; ///< 
    std::list<int32_t> mNodes;       ///< 
};

#endif // _NAVPATH_H
}}
