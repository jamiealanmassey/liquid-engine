#include "NavNode.h"

NavNode::NavNode(int32_t index) :
	m_Traversable(true),
	m_Position(sf::Vector2f()),
	m_Index(index)
{
}

NavNode::~NavNode()
{
}

NavEdge::NavEdge() :
	m_From(INVALID_NODE_INDEX),
	m_To(INVALID_NODE_INDEX),
	m_Cost(1.0f)
{
}

NavEdge::NavEdge(int32_t from, int32_t to, double cost) :
	m_From(from),
	m_To(to),
	m_Cost(cost)
{
}

NavEdge::~NavEdge()
{
}
