#include "NavNode.h"

namespace liquid {
namespace navigation {

    NavNode::NavNode(int32_t index)
    {
        mTraversable = true;
        mPositionX = 0.0f;
        mPositionY = 0.0f;
        mNodeIndex = index;
    }

    NavNode::~NavNode()
    {}

    void NavNode::setPosition(float x, float y)
    {
        mPositionX = x;
        mPositionY = y;
    }

    void NavNode::setPosition(std::array<float, 2> position)
    {
        mPositionX = position[0];
        mPositionY = position[1];
    }

    void NavNode::setTraversable(bool flag)
    {
        mTraversable = flag;
    }

    void NavNode::setNodeIndex(int32_t index)
    {
        mNodeIndex = index;
    }

    const float NavNode::getPositionX() const
    {
        return mPositionX;
    }

    const float NavNode::getPositionY() const
    {
        return mPositionY;
    }
    
    const bool NavNode::isTraversable() const
    {
        return mTraversable;
    }

    const int32_t NavNode::getNodeIndex() const
    {
        return mNodeIndex;
    }

}}
