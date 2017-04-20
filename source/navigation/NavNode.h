#include <array>

namespace liquid { namespace navigation {
#ifndef _NAVNODE_H
#define _NAVNODE_H

#define INVALID_NAV_NODE -1

class NavNode
{
public:
    NavNode(int32_t index);
    ~NavNode();

    void setPosition(float x, float y);
    void setPosition(std::array<float, 2> position);
    void setTraversable(bool flag);
    void setNodeIndex(int32_t index);

    const float getPositionX() const;
    const float getPositionY() const;
    const bool isTraversable() const;
    const int32_t getNodeIndex() const;

protected:
    float   mPositionX;   ///< 
    float   mPositionY;   ///< 
    bool    mTraversable; ///< 
    int32_t mNodeIndex;   ///< 
};

#endif // _NAVNODE_H
}}
