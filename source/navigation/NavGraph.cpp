#include "NavGraph.h"
#include "../Utilities/PriorityQueue.h"

#include <algorithm>
#include <unordered_set>
#include <cassert>

NavGraph::NavGraph(bool directed) :
	m_Directed(directed)
{}

void NavGraph::update(float delta)
{
}

void NavGraph::render(sf::RenderTarget& target)
{
	// Setup line shape
	sf::VertexArray edge_shape(sf::PrimitiveType::Lines);

	// Render edges
	for (auto& edges : m_Edges)
	{
		NavEdgeList::iterator it = edges.begin();
		for (; it != edges.end(); it++)
		{
			edge_shape.append(sf::Vertex(getNode(it->m_From).getPosition(), sf::Color::Blue));
			edge_shape.append(sf::Vertex(getNode(it->m_To).getPosition(), sf::Color::Blue));
		}
	}

	target.draw(edge_shape);

	// Setup node shape
	sf::RectangleShape node_shape;
	node_shape.setFillColor(sf::Color::Blue);
	node_shape.setSize(sf::Vector2f(4.0f, 4.0f));

	// Render nodes
	for (uint32_t i = 0; i < m_Nodes.size(); i++)
	{
		if (!m_Nodes[i].checkTraversable())
			node_shape.setFillColor(sf::Color::Red);
		else
			node_shape.setFillColor(sf::Color::Blue);

		node_shape.setPosition(m_Nodes[i].getPosition());
		target.draw(node_shape);
	}
}

const NavNode& NavGraph::getNode(int32_t idx) const
{
	// Make sure index is in range
	assert(idx < (int32_t)m_Nodes.size() && idx >= 0 &&
		"<NavGraph::GetNode>: invalid index");

	// Return node at index
	return m_Nodes[idx];
}

NavNode& NavGraph::getNode(int32_t idx)
{
	// Make sure index is in range
	assert(idx < (int32_t)m_Nodes.size() && idx >= 0 &&
		"<NavGraph::GetNode>: invalid index");

	// Return node at index
	return m_Nodes[idx];
}

const NavEdge& NavGraph::getEdge(int32_t from, int32_t to) const
{
	// Check for valid from index
	assert(from < m_Nodes.size() && from >= 0 && m_Nodes[from].getIndex() != INVALID_NODE_INDEX &&
		"<NavGraph::getEdge>: invalid 'from' index");

	// Check for valid to index
	assert(to < m_Nodes.size() && to >= 0 && m_Nodes[to].getIndex() != INVALID_NODE_INDEX &&
		"<NavGraph::getEdge>: invalid 'to' index");

	// Find edge
	for (NavEdgeList::const_iterator cur_edge = m_Edges[from].begin();
	cur_edge != m_Edges[from].end(); ++cur_edge)
	{
		if (cur_edge->m_To == to)
			return *cur_edge;
	}

	// Couldn't find edge
	assert(0 && "<NavGraph::getEdge>: edge doesn't exist");
}

NavEdge& NavGraph::getEdge(int32_t from, int32_t to)
{
	// Check for valid from index
	assert(from < m_Nodes.size() && from >= 0 && m_Nodes[from].getIndex() != INVALID_NODE_INDEX &&
		"<NavGraph::getEdge>: invalid 'from' index");

	// Check for valid to index
	assert(to < m_Nodes.size() && to >= 0 && m_Nodes[to].getIndex() != INVALID_NODE_INDEX &&
		"<NavGraph::getEdge>: invalid 'to' index");

	// Find edge
	for (NavEdgeList::iterator cur_edge = m_Edges[from].begin();
	cur_edge != m_Edges[from].end(); ++cur_edge)
	{
		if (cur_edge->m_To == to)
			return *cur_edge;
	}

	// Couldn't find edge
	assert(0 && "<NavGraph::getEdge>: edge doesn't exist");
}

int32_t NavGraph::addNode(sf::Vector2f pos, bool traversable)
{
	// Calculate index
	int32_t index = m_Nodes.size();

	// Create new node
	NavNode new_node(index);
	new_node.setPosition(pos);
	new_node.setTraversable(traversable);

	// And add it to the list
	m_Nodes.push_back(new_node);
	m_Edges.push_back(NavEdgeList());
	return index;
}

void NavGraph::addEdge(int32_t from, int32_t to, double cost)
{
	// Add the edge to the graph
	if ((m_Nodes[to].getIndex() != INVALID_NODE_INDEX) &&
		(m_Nodes[from].getIndex() != INVALID_NODE_INDEX))
	{
		// Add edge
		if (isEdgeUnique(from, to))
			m_Edges[from].push_back(NavEdge(from, to, cost));

		// Add reverse edge if not directed
		if (!m_Directed && isEdgeUnique(to, from))
			m_Edges[to].push_back(NavEdge(to, from, cost));
	}
}

void NavGraph::removeEdge(int32_t from, int32_t to)
{
	// Make sure the nodes exist
	assert(from < (int32_t)m_Nodes.size() && to < (int32_t)m_Nodes.size() &&
		"<NavGraph::removeEdge>: node doesn't exist at index");

	// Remove the edge
	NavEdgeList::iterator cur_edge;

	if (!m_Directed)
	{
		for (cur_edge = m_Edges[to].begin(); cur_edge != m_Edges[to].end(); ++cur_edge)
		{
			if (cur_edge->m_To == from)
			{
				cur_edge = m_Edges[to].erase(cur_edge);
				break;
			}
		}
	}

	for (cur_edge = m_Edges[from].begin(); cur_edge != m_Edges[from].end(); ++cur_edge)
	{
		if (cur_edge->m_To == to)
		{
			cur_edge = m_Edges[from].erase(cur_edge);
			break;
		}
	}
}

bool NavGraph::isNodePresent(int32_t idx) const
{
	return !((m_Nodes[idx].getIndex() == INVALID_NODE_INDEX) ||
		(idx >= m_Nodes.size()));
}

bool NavGraph::isEdgePresent(int32_t from, int32_t to) const
{
	if (isNodePresent(from) && isNodePresent(to))
	{
		for (NavEdgeList::const_iterator cur_edge = m_Edges[from].begin();
		cur_edge != m_Edges[from].end(); ++cur_edge)
		{
			if (cur_edge->m_To == to)
				return true;
		}

		return false;
	}
	else
		return false;
}

bool NavGraph::isEdgeUnique(int32_t from, int32_t to) const
{
	// Check for the edge being unique
	NavEdgeList::const_iterator cur_edge = m_Edges[from].begin();
	for (; cur_edge != m_Edges[from].end(); ++cur_edge)
	{
		if (cur_edge->m_To == to)
			return false;
	}

	// Edge was unique
	return true;
}

void NavGraph::clear()
{
	m_Nodes.clear();
	m_Edges.clear();
}

void NavGraph::removeEdges()
{
	for (NavEdges::iterator it = m_Edges.begin(); it != m_Edges.end(); ++it)
		it->clear();
}

void NavGraph::cullInvalidEdges()
{
	for (NavEdges::iterator cur_edges = m_Edges.begin(); cur_edges != m_Edges.end(); ++cur_edges)
	{
		for (NavEdgeList::iterator cur_edge = (*cur_edges).begin(); cur_edge != (*cur_edges).end(); ++cur_edge)
		{
			if (m_Nodes[cur_edge->m_To].getIndex() == INVALID_NODE_INDEX ||
				m_Nodes[cur_edge->m_From].getIndex() == INVALID_NODE_INDEX)
			{
				cur_edge = (*cur_edges).erase(cur_edge);
			}
		}
	}
}

std::vector<sf::Vector2i> NavGraph::toVector2i(std::list<NavNode>& nodes)
{
	// Create Container
	std::vector<sf::Vector2i> result;

	// Compile nodes into container
	for (auto node : nodes)
		result.push_back(sf::Vector2i(node.getPosition()));

	// Return
	return result;
}

int32_t NavGraph::numNodesActive() const
{
	// Store count
	int32_t count = 0;

	// Find active nodes
	for (uint32_t n = 0; n < m_Nodes.size(); ++n)
	{
		if (m_Nodes[n].getIndex() != INVALID_NODE_INDEX)
			++count;
	}

	// Return count
	return count;
}

int32_t NavGraph::numEdges() const
{
	// Store total edges
	int total = 0;

	// Find total edges
	for (NavEdges::const_iterator cur_edge = m_Edges.begin(); cur_edge != m_Edges.end(); ++cur_edge)
		total += cur_edge->size();

	// Return total
	return total;
}
