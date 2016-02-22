#ifndef _A_STAR_H
#define _A_STAR_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <unordered_set>

class NavGraph;
class NavPath;
class NavNode;

class AStar
{
public:
	typedef std::function<double(sf::Vector2f, sf::Vector2f)> Heuristic;

public:
	AStar(NavGraph* graph, Heuristic heuristic = std::bind(&AStar::manhattan, std::placeholders::_1, std::placeholders::_2));
	~AStar() {}

	/* Core functionality */
	NavPath* search(int32_t source_node, int32_t target_node);

	/* Comparison function for PriorityQueue */
	bool compareNodes(int32_t a, int32_t b);

	/* Pre-defined heuristics */
	static double manhattan(sf::Vector2f v1, sf::Vector2f v2);
	static double euclidian(sf::Vector2f v1, sf::Vector2f v2);

protected:
	NavGraph*			m_Graph;	 ///< Pointer to given graph
	Heuristic			m_Heuristic; ///< Heuristic function
	std::vector<double> m_GCosts;	 ///< Stored g costs
	std::vector<double> m_FCosts;	 ///< Stored f costs
};

#endif // _A_STAR_H
