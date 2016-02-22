#ifndef _NAVGRAPH_H
#define _NAVGRAPH_H

#include "NavNode.h"

class NavPath;
class NavGraph
{
public:
	NavGraph(bool directed);
	~NavGraph() {}

	/* Core control functions */
	void update(float delta);
	void render(sf::RenderTarget& target);

	/* Getters for nodes */
	const NavNode& getNode(int32_t idx) const;
		  NavNode& getNode(int32_t idx);

	/* Getters for edges */
	const NavEdge& getEdge(int32_t from, int32_t to) const;
		  NavEdge& getEdge(int32_t from, int32_t to);

	/* Adding and general node control functions */
	int32_t addNode(sf::Vector2f pos, bool traversable = true);
	void	addEdge(int32_t from, int32_t to, double cost);
	void	removeEdge(int32_t from, int32_t to);

	/* Getters to check if a node/edge is present */
	bool isNodePresent(int32_t idx)				 const;
	bool isEdgePresent(int32_t from, int32_t to) const;
	bool isEdgeUnique(int32_t from, int32_t to)  const;

	/* Setter func for direciton */
	void setDirected(bool directed) { m_Directed = directed; }

	/* Misc control functions */
	void clear();
	void removeEdges();
	void cullInvalidEdges();

	/* Getter for nodes as positions */
	std::vector<sf::Vector2i> toVector2i(std::list<NavNode>& nodes);

	/* Getters for edges and nodes */
	int32_t numNodesActive() const;
	int32_t numEdges()		 const;

	/* Getters for flags and node counts */
	int32_t numNodes()    const { return m_Nodes.size(); }
	bool    isEmpty()     const { return m_Nodes.empty(); }
	bool    getDirected() const { return m_Directed; }

	/* Getters for nodes */
	NavNodes& getNodesAsRef() { return m_Nodes; }
	NavEdges& getEdgesAsRef() { return m_Edges; }

protected:
	NavNodes m_Nodes;	 ///< List of nodes in graph
	NavEdges m_Edges;	 ///< List of edges in the graph
	bool	 m_Directed; ///< Flag denoting if the graph is directed
};

#endif // _NAVGRAPH_H
