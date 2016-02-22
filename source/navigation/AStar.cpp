#include "AStar.h"
#include "../Navigation/NavGraph.h"
#include "../Navigation/NavNode.h"
#include "../Navigation/NavPath.h"
#include "../Utilities/PriorityQueue.h"

AStar::AStar(NavGraph* graph, Heuristic heuristic) :
	m_Graph(graph),
	m_Heuristic(heuristic)
{
}

NavPath* AStar::search(int32_t source_node, int32_t target_node)
{
	if (target_node == -1)
		return nullptr;

	// Make sure we aren't trying to find a path to the same node as the source
	if (source_node == target_node)
		return nullptr;

	if (!m_Graph->getNode(target_node).checkTraversable())
	{
		NavPath* path = new NavPath(m_Graph);
		path->pushFront(source_node);
		return path;
	}

	// For convenience
	NavNodes& nodes = m_Graph->getNodesAsRef();
	NavEdges& edges = m_Graph->getEdgesAsRef();
	NavNode&  source = nodes[source_node];
	NavNode&  target = nodes[target_node];
	int32_t   num_nodes = m_Graph->numNodes();

	// Create an open list
	PriorityQueueMin       open_list(num_nodes, std::bind(&AStar::compareNodes, this, 
		std::placeholders::_1, std::placeholders::_2));

	// Create a closed list and came from vector
	std::unordered_set<int32_t> closed_list;
	std::vector<int32_t>        came_from;

	// Resize & clear SPT, Costs & came_from
	m_GCosts.resize(num_nodes, 0.0f);
	m_FCosts.resize(num_nodes, 0.0f);
	came_from.resize(num_nodes, INVALID_NODE_INDEX);

	// Place the source node at the top of the Priority Queue
	open_list.insert(source_node);

	// Assign g costs and f costs
	m_GCosts[source_node] = 0;
	m_FCosts[source_node] = m_Heuristic(source.getPosition(), target.getPosition());

	// A* Pathfinding Algorithm
	while (!open_list.isEmpty())
	{
		// Find closest node and add to Shortest Path Tree (SPT)
		int32_t closest_node = open_list.pop(0);
		closed_list.insert(closest_node);

		// We have reached our destination!
		if (closest_node == target_node)
			break;

		// Expand Current Node
		NavEdgeList::iterator it = edges[closest_node].begin();
		for (; it != edges[closest_node].end(); ++it)
		{
			if (closed_list.find((*it).m_To) != closed_list.end())
				continue; // Already evaluated node

			if (!nodes[(*it).m_To].checkTraversable())
				continue; // Edge not traversable

			float g_cost = (float)(m_GCosts[closest_node] + (*it).m_Cost);
			float h_cost = (float)(m_Heuristic(nodes[(*it).m_To].getPosition(), nodes[target_node].getPosition()));
			bool  open = open_list.contains((*it).m_To);

			if (!open || g_cost < m_GCosts[(*it).m_To])
			{
				came_from[(*it).m_To] = closest_node;
				m_FCosts[(*it).m_To] = g_cost + h_cost;
				m_GCosts[(*it).m_To] = g_cost;

				if (!open_list.contains((*it).m_To))
					open_list.insert((*it).m_To);

				else
					open_list.updatePriority((*it).m_To);
			}
		}
	}

	// See if it actually found a path
	if (open_list.isEmpty())
		return nullptr;

	// Construct pathfinding path
	NavPath* path = new NavPath(m_Graph);
	int32_t  node = target_node;

	while (node != source_node)
	{
		path->pushFront(node);
		node = came_from[node];
	}

	path->pushFront(source_node);
	return path;
}

double AStar::manhattan(sf::Vector2f v1, sf::Vector2f v2)
{
	// Calculate Difference
	double difference_x = abs(v1.x - v2.x);
	double difference_y = abs(v1.y - v2.y);

	// Return Manhattan
	return (difference_x + difference_y);
}

double AStar::euclidian(sf::Vector2f v1, sf::Vector2f v2)
{
	// Calculate seperation
	double difference_x = v1.x - v2.x;
	double difference_y = v1.y - v2.y;

	// Calculate heuristic
	return sqrt(difference_x * difference_x + difference_y * difference_y);
}

bool AStar::compareNodes(int32_t a, int32_t b)
{
	return (m_FCosts[a] < m_FCosts[b]);
}
