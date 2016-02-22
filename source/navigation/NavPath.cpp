#include "NavPath.h"

NavPath::NavPath(NavGraph* graph) :
	m_Graph(graph)
{
}

void NavPath::render(sf::RenderTarget& target)
{
	// Setup node shape
	/*RectangleShape node_shape;
	node_shape.setFillColor(Color::Yellow);
	node_shape.setSize(Vector2f(8.0f, 8.0f));

	list<int32_t>::iterator it = m_Nodes.begin();
	for (; it != m_Nodes.end(); it++)
	{
	node_shape.setPosition(m_Graph->GetNode(*it).GetPosition());
	target.draw(node_shape);
	}*/
}

const NavNode& NavPath::popFront()
{
	const NavNode& node = peekFront();
	m_Nodes.pop_front();
	return node;
}

const NavNode& NavPath::popBack()
{
	const NavNode& node = peekBack();
	m_Nodes.pop_back();
	return node;
}

const NavNode& NavPath::loopFront()
{
	// Pop front node and add it to the back
	pushBack(m_Nodes.front());
	return popFront();
}

const NavNode& NavPath::loopBack()
{
	// Pop back node and add it to the front
	pushFront(m_Nodes.back());
	return popBack();
}

std::vector<NavNode> NavPath::getPath()
{
	std::vector<NavNode> list;

	for (auto node : m_Nodes)
		list.push_back(m_Graph->getNode(node));

	return list;
}

std::vector<NavNode> NavPath::getPathReverse()
{
	std::list<int32_t>::reverse_iterator it = m_Nodes.rbegin();
	std::vector<NavNode> list;

	if (m_Nodes.empty())
		return list;

	for(; it != m_Nodes.rend(); ++it)
		list.push_back(m_Graph->getNode(*it));

	return list;
}
